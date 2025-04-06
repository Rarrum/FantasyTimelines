module;

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>
#include <QSpacerItem>
#include <QScrollArea>

#include <unordered_set>
#include <string>
#include <limits>
#include <concepts>

import WorldState;
import QTrackedWidget;

export module CharacterGui;

namespace
{
    //LATER: For now we're going to code this to a DnD character specifically.. though ideally it would be fully generic

    std::vector<std::string> DefaultPrimaryStats
    {
        "Strength",
        "Dexterity",
        "Constitution",
        "Intelligence",
        "Wisdom",
        "Charisma"
    };

    std::vector<std::string> DefaultSkills
    {
        "Acrobatics",
        "Animal Handling",
        "Arcana",
        "Athletics",
        "Deception",
        "History",
        "Insight",
        "Intimidation",
        "Investigation",
        "Medicine",
        "Nature",
        "Perception",
        "Performance",
        "Persuasion",
        "Religion",
        "Sleight of Hand",
        "Stealth",
        "Survival"
    };

    std::vector<std::string> DefaultHitDice
    {
        "D4",
        "D6",
        "D8",
        "D10",
        "D12"
    };
}

export class CharacterGui : public QTrackedWidget
{
public:
    CharacterGui(std::string characterName)
    {
        setWindowTitle("Fantasy Timelines - Character");
        name = characterName;

        OnChangeTimelineView();
        show();
    }

    void OnChangeTimelineView() override
    {
        // Free all widgets and recreate the top layout
        if (topLayout)
            delete topLayout; // also deletes all children

        topLayout = CreateOwnedWidget<QVBoxLayout>();
        topLayout->setAlignment(Qt::AlignTop);
        setLayout(topLayout);
        topLayout->setEnabled(false);

        const Character *c = FindCharacter(GlobalWorld.CurrentView(), name);
        if (!c)
            return;

        // Create and set up all tabs
        topLayout->setEnabled(true);
        setWindowTitle(QString::fromStdString("Fantasy Timelines - Character - " + c->Name));

        auto tabs = CreateOwnedWidget<QTabWidget>();
        topLayout->addWidget(tabs);

        CreateStatsTab(tabs, *c);
        CreateHealthTab(tabs, *c);
        CreateActionsTab(tabs, *c);
        CreateAbilitiesTab(tabs, *c);
        CreateItemsTab(tabs, *c);
        CreateSpellsTab(tabs, *c);
        CreateResistsTab(tabs, *c);
        CreateClassTab(tabs, *c);
        CreateLoreTab(tabs, *c);
    }

private:
    QVBoxLayout *topLayout = nullptr;
    std::string name;

    void CreateStatsTab(QTabWidget *tabs, const Character &c)
    {
        auto tabStats = CreateOwnedWidget<QWidget>();
        tabs->addTab(tabStats, "Stats");

        auto statsMainLayout = CreateOwnedWidget<QVBoxLayout>();
        tabStats->setLayout(statsMainLayout);

        auto statsTopLayout = CreateOwnedWidget<QGridLayout>();
        statsMainLayout->addLayout(statsTopLayout);

        auto statsGeneralLayout = AddGroupBoxWithLayout<QGridLayout>(statsTopLayout, "General", 1, 0);

        AddNumberField(statsGeneralLayout, "Armor Class", FindStatValue(c, "Armor Class"), 0, 0);
        AddNumberField(statsGeneralLayout, "Speed", FindStatValue(c, "Speed"), 0, 2);
        AddNumberField(statsGeneralLayout, "Proficiency Bonus", FindStatValue(c, "Proficiency Bonus"), 0, 4);
        AddNumberField(statsGeneralLayout, "Passive Perception", FindStatValue(c, "Passive Perception"), 0, 6);

        auto statsBottomLayout = CreateOwnedWidget<QHBoxLayout>();
        statsMainLayout->addLayout(statsBottomLayout);

        auto statsLeftLayout = CreateOwnedWidget<QVBoxLayout>();
        statsBottomLayout->addLayout(statsLeftLayout);
        
        auto primaryStatsLayout = AddGroupBoxWithLayout<QGridLayout>(statsLeftLayout, "Primary Stats");
        for (const std::string &s : DefaultPrimaryStats)
            AddNumberField(primaryStatsLayout, s, FindStatValue(c, s), primaryStatsLayout->rowCount(), 0);

        auto primarySavesLayout = AddGroupBoxWithLayout<QGridLayout>(statsLeftLayout, "Saving Throws");
        for (const std::string &s : DefaultPrimaryStats)
            AddNumberField(primarySavesLayout, s, FindStatValue(c, s), primarySavesLayout->rowCount(), 0);

        auto skillsLayout = AddGroupBoxWithLayout<QGridLayout>(statsBottomLayout, "Skills");
        for (const std::string& skill : DefaultSkills)
            AddNumberField(skillsLayout, skill, FindStatValue(c, skill), skillsLayout->rowCount(), 0);
    }

    void CreateHealthTab(QTabWidget *tabs, const Character &c)
    {
        auto tabHealth = CreateOwnedWidget<QWidget>();
        tabs->addTab(tabHealth, "Health");

        auto healthLayout = CreateOwnedWidget<QGridLayout>();
        tabHealth->setLayout(healthLayout);

        auto healthFluidLayout = AddGroupBoxWithLayout<QGridLayout>(healthLayout, "Health", 0, 0, 1, 2);

        AddNumberField(healthFluidLayout, "Current HP", FindStatValue(c, "Current HP"), 0, 0);
        AddNumberField(healthFluidLayout, "Max HP", FindStatValue(c, "Max HP"), 0, 2);
        AddNumberField(healthFluidLayout, "Temp HP", FindStatValue(c, "Temp HP"), 1, 0);

        auto healthHitDieLayout = AddGroupBoxWithLayout<QGridLayout>(healthLayout, "Hit Die", 1, 0);
        for (const std::string& die : DefaultHitDice)
            AddNumberField(healthHitDieLayout, die, FindStatValue(c, die), healthHitDieLayout->rowCount(), 0);

        auto healthDeathSavesLayout = AddGroupBoxWithLayout<QGridLayout>(healthLayout, "Death Saves", 1, 1);
        AddNumberField(healthDeathSavesLayout, "Successes", FindStatValue(c, "Successes"), 0, 0);
        AddNumberField(healthDeathSavesLayout, "Failures", FindStatValue(c, "Failures"), 0, 2);

        auto healthConditionsLayout = AddGroupBoxWithLayout<QGridLayout>(healthLayout, "Conditions", 2, 0);
        AddNumberField(healthConditionsLayout, "Conditions", FindStatValue(c, "Conditions"), 0, 0);

        auto healthEffectsLayout = AddGroupBoxWithLayout<QGridLayout>(healthLayout, "Effects", 2, 1);
        AddNumberField(healthEffectsLayout, "Effects", FindStatValue(c, "Effects"), 0, 0);
    }

    void CreateActionsTab(QTabWidget *tabs, const Character &c)
    {
        auto tabActions = CreateOwnedWidget<QWidget>();
        tabs->addTab(tabActions, "Actions");

        auto actionsMainLayout = CreateOwnedWidget<QGridLayout>();
        tabActions->setLayout(actionsMainLayout);

        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(actionsMainLayout, "Actions", 0, 0, 2, 1);
        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(actionsMainLayout, "Bonus Actions", 0, 1);
        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(actionsMainLayout, "Reactions", 1, 1);
    }

    void CreateAbilitiesTab(QTabWidget *tabs, const Character &c)
    {
        auto tabAbilities = CreateOwnedWidget<QWidget>();
        tabs->addTab(tabAbilities, "Abilities");

        auto abilitiesMainLayout = CreateOwnedWidget<QGridLayout>();
        tabAbilities->setLayout(abilitiesMainLayout);

        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(abilitiesMainLayout, "Passive", 0, 0);
        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(abilitiesMainLayout, "Proficiencies", 0, 1);
    }

    void CreateItemsTab(QTabWidget *tabs, const Character &c)
    {
        auto tabItems = CreateOwnedWidget<QWidget>();
        tabs->addTab(tabItems, "Items");

        auto itemsMainLayout = CreateOwnedWidget<QGridLayout>();
        tabItems->setLayout(itemsMainLayout);

        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(itemsMainLayout, "Equipped", 0, 0);
        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(itemsMainLayout, "Currency", 1, 0);
        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(itemsMainLayout, "Ammo", 2, 0);
        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(itemsMainLayout, "Inventory", 0, 1, 3, 1);
    }

    void CreateSpellsTab(QTabWidget *tabs, const Character &c)
    {
        auto tabSpells = CreateOwnedWidget<QWidget>();
        tabs->addTab(tabSpells, "Spells");

        auto *spellsDummyLayout = CreateOwnedWidget<QVBoxLayout>();
        spellsDummyLayout->setContentsMargins(0, 0, 0, 0);
        tabSpells->setLayout(spellsDummyLayout);

        auto spellsScroller = CreateOwnedWidget<QScrollArea>();
        spellsScroller->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        spellsScroller->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        spellsScroller->setWidgetResizable(true);
        spellsScroller->setContentsMargins(0, 0, 0, 0);
        spellsDummyLayout->addWidget(spellsScroller);

        auto *spellsMainWidget = CreateOwnedWidget<QWidget>();
        spellsMainWidget->setContentsMargins(0, 0, 0, 0);
        spellsScroller->setWidget(spellsMainWidget);

        auto spellsMainLayout = CreateOwnedWidget<QVBoxLayout>();
        spellsMainWidget->setLayout(spellsMainLayout);

        for (int i = 0; i < 10; ++i)
        {
            auto levelLayout = AddGroupBoxWithLayout<QGridLayout>(spellsMainLayout, "Level " + std::to_string(i));
            AddTextField(levelLayout, "Spells", GetSpellList(c, i), 0, 0);
        }
    }

    void CreateResistsTab(QTabWidget *tabs, const Character &c)
    {
        auto tabResists = CreateOwnedWidget<QWidget>();
        tabs->addTab(tabResists, "Resists");

        auto resistsMainLayout = CreateOwnedWidget<QGridLayout>();
        tabResists->setLayout(resistsMainLayout);

        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(resistsMainLayout, "Resistance", 0, 0);
        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(resistsMainLayout, "Immunity", 1, 0);
        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(resistsMainLayout, "Weakness", 0, 1);
        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(resistsMainLayout, "Inversion", 1, 1);
    }

    void CreateClassTab(QTabWidget *tabs, const Character &c)
    {
        auto tabClass = CreateOwnedWidget<QWidget>();
        tabs->addTab(tabClass, "Class");

        auto *classLayout = CreateOwnedWidget<QVBoxLayout>();
        tabClass->setLayout(classLayout);

        auto classCharacterLayout = AddGroupBoxWithLayout<QGridLayout>(classLayout, "Character");
        
        // Replace the number fields with text fields showing actual character origins
        AddTextField(classCharacterLayout, "Species", GetModifierList(c.Species), 0, 0);
        AddTextField(classCharacterLayout, "Background", GetModifierList(c.Backgrounds), 0, 2);
        AddTextField(classCharacterLayout, "Feats", GetModifierList(c.Feats), 0, 4); //TODO: probably belongs somewhere else
        AddTextField(classCharacterLayout, "Alignment", "Maybe Good", 1, 0);

        auto classClassLayout = AddGroupBoxWithLayout<QGridLayout>(classLayout, "Classes");

        for (size_t i = 0; i < c.Classes.size(); ++i)
        {
            const auto &characterClass = c.Classes[i];
            AddTextField(classClassLayout, "Class", characterClass.Class, i, 0);
            AddTextField(classClassLayout, "Subclass", characterClass.Subclass, i, 2);
            AddNumberField(classClassLayout, "Level", characterClass.Level, i, 4);
        }
    }

    void CreateLoreTab(QTabWidget *tabs, const Character &c)
    {
        auto tabLore = CreateOwnedWidget<QWidget>();
        tabs->addTab(tabLore, "Lore");
    }

    template <typename BoxLayoutType, typename ParentLayoutType, typename ...Args>
    requires (std::derived_from<BoxLayoutType, QLayout>, std::derived_from<ParentLayoutType, QLayout>)
    BoxLayoutType* AddGroupBoxWithLayout(ParentLayoutType *target, const std::string &name, Args&& ...addWidgetArgs)
    {
        auto box = CreateOwnedWidget<QGroupBox>(QString::fromStdString(name));
        target->addWidget(box, std::forward<Args>(addWidgetArgs)...);

        auto layout = new BoxLayoutType();
        layout->setAlignment(Qt::AlignCenter);
        box->setLayout(layout);
        return layout;
    }

    void AddNumberField(QGridLayout *target, const std::string &name, int32_t value, int row, int col)
    {
        auto label = CreateOwnedWidget<QLabel>(QString::fromStdString(name + ":"));
        target->addWidget(label, row, col, Qt::AlignLeft);

        auto *lineEdit = CreateOwnedWidget<QLineEdit>();
        lineEdit->setReadOnly(true);
        lineEdit->setValidator(CreateOwnedWidget<QIntValidator>(std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max()));
        lineEdit->setMinimumWidth(50);
        lineEdit->setMaximumWidth(50);
        lineEdit->setText(QString::number(value));
        target->addWidget(lineEdit, row, col + 1, Qt::AlignLeft);
    }

    void AddTextField(QGridLayout *target, const std::string &name, const std::string &text, int row, int col)
    {
        auto label = CreateOwnedWidget<QLabel>(QString::fromStdString(name + ":"));
        target->addWidget(label, row, col, Qt::AlignLeft);

        auto *lineEdit = CreateOwnedWidget<QLineEdit>();
        lineEdit->setReadOnly(true);
        lineEdit->setMinimumWidth(100);
        lineEdit->setText(QString::fromStdString(text));
        target->addWidget(lineEdit, row, col + 1, Qt::AlignLeft);
    }

    static int32_t FindStatValue(const Character &c, const std::string &statName)
    {
        auto it = std::find_if(c.BaseStats.begin(), c.BaseStats.end(), [&](const auto &stat) { return stat.Name == statName; });
        return it != c.BaseStats.end() ? it->Value : 0;
    }

    static std::string GetSpellList(const Character &c, uint32_t level)
    {
        std::string result;
        for (const auto &spell : c.Spells)
        {
            if (spell.Level == level)
            {
                if (!result.empty())
                    result += ", ";
                result += spell.Name;
            }
        }
        return result;
    }

    // Add new helper method
    static std::string GetModifierList(const std::vector<CharacterModifier> &modifiers)
    {
        std::string result;
        for (const auto &modifier : modifiers)
        {
            if (!result.empty())
                result += ", ";
            result += modifier.Name;
        }
        return result;
    }
};
