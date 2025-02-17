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
    std::vector<std::string> DefaultPrimaryStats
    {
        "Strength",
        "Dexterity",
        "Constitution",
        "Intelligence",
        "Wisdom",
        "Charisma"
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
        if (topLayout)
            delete topLayout; // also deletes all children
        topLayout = new QVBoxLayout();

        topLayout->setAlignment(Qt::AlignTop);
        setLayout(topLayout);

        topLayout->setEnabled(false);
        const Character *c = FindCharacter(GlobalWorld.CurrentView(), name);
        if (!c)
            return;

        topLayout->setEnabled(true);
        setWindowTitle(QString::fromStdString("Fantasy Timelines - Character - " + c->Name));

        auto tabs = new QTabWidget();
        topLayout->addWidget(tabs);

        // Stats tab
        auto tabStats = new QWidget();
        tabs->addTab(tabStats, "Stats");

        auto statsMainLayout = new QVBoxLayout();
        tabStats->setLayout(statsMainLayout);

        auto statsTopLayout = new QGridLayout();
        statsMainLayout->addLayout(statsTopLayout);

        auto statsGeneralLayout = AddGroupBoxWithLayout<QGridLayout>(statsTopLayout, "General", 1, 0);

        AddNumberField(statsGeneralLayout, "Armor Class", 0, 0);
        AddNumberField(statsGeneralLayout, "Speed", 0, 2);
        AddNumberField(statsGeneralLayout, "Proficiency Bonus", 0, 4);
        AddNumberField(statsGeneralLayout, "Passive Perception", 0, 6);

        auto statsBottomLayout = new QHBoxLayout();
        statsMainLayout->addLayout(statsBottomLayout);

        auto primaryStatsLayout = AddGroupBoxWithLayout<QGridLayout>(statsBottomLayout, "Primary Stats");

        for (const std::string &s : DefaultPrimaryStats)
            AddNumberField(primaryStatsLayout, s, primaryStatsLayout->rowCount(), 0);

        auto primarySavesLayout = AddGroupBoxWithLayout<QGridLayout>(statsBottomLayout, "Saving Throws");

        for (const std::string &s : DefaultPrimaryStats)
            AddNumberField(primarySavesLayout, s, primarySavesLayout->rowCount(), 0);

        auto skillsLayout = AddGroupBoxWithLayout<QGridLayout>(statsBottomLayout, "Skills");

        AddNumberField(skillsLayout, "Cat Handling", 0, 0);
        AddNumberField(skillsLayout, "Stealth", 1, 0);
        AddNumberField(skillsLayout, "TODO all the rest", 2, 0);

        // Health tab
        auto tabHealth = new QWidget();
        tabs->addTab(tabHealth, "Health");

        auto healthLayout = new QGridLayout();
        tabHealth->setLayout(healthLayout);

        auto healthFluidLayout = AddGroupBoxWithLayout<QGridLayout>(healthLayout, "Health", 0, 0, 1, 2);

        AddNumberField(healthFluidLayout, "Current HP", 0, 0);
        AddNumberField(healthFluidLayout, "Max HP", 0, 2);
        AddNumberField(healthFluidLayout, "Temp HP", 1, 0);

        auto healthHitDieLayout = AddGroupBoxWithLayout<QGridLayout>(healthLayout, "Hit Die", 1, 0);

        AddNumberField(healthHitDieLayout, "1D8", 0, 0);

        auto healthDeathSavesLayout = AddGroupBoxWithLayout<QGridLayout>(healthLayout, "Death Saves", 1, 1);

        AddNumberField(healthDeathSavesLayout, "Successes", 0, 0);
        AddNumberField(healthDeathSavesLayout, "Failures", 0, 2);

        auto healthConditionsLayout = AddGroupBoxWithLayout<QGridLayout>(healthLayout, "Conditions", 2, 0);

        AddNumberField(healthConditionsLayout, "Conditions", 0, 0); // prone etc

        auto healthEffectsLayout = AddGroupBoxWithLayout<QGridLayout>(healthLayout, "Effects", 2, 1);

        AddNumberField(healthEffectsLayout, "Effects", 0, 0); // buffs / debuffs

        // Actions tab
        auto tabActions = new QWidget();
        tabs->addTab(tabActions, "Actions");

        auto actionsMainLayout = new QGridLayout();
        tabActions->setLayout(actionsMainLayout);

        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(actionsMainLayout, "Actions", 0, 0, 2, 1);
        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(actionsMainLayout, "Bonus Actions", 0, 1);
        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(actionsMainLayout, "Reactions", 1, 1);

        // Abilities tab
        auto tabAbilities = new QWidget();
        tabs->addTab(tabAbilities, "Abilities");

        auto abilitiesMainLayout = new QGridLayout();
        tabAbilities->setLayout(abilitiesMainLayout);

        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(abilitiesMainLayout, "Passive", 0, 0);
        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(abilitiesMainLayout, "Proficiencies", 0, 1);

        // Items tab
        auto tabItems = new QWidget();
        tabs->addTab(tabItems, "Items");

        auto itemsMainLayout = new QGridLayout();
        tabItems->setLayout(itemsMainLayout);

        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(itemsMainLayout, "Equipped", 0, 0);
        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(itemsMainLayout, "Currency", 1, 0);
        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(itemsMainLayout, "Ammo", 2, 0);
        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(itemsMainLayout, "Inventory", 0, 1, 3, 1);

        // Spells tab
        auto tabSpells = new QWidget();
        tabs->addTab(tabSpells, "Spells");

        auto *spellsDummyLayout = new QVBoxLayout();
        spellsDummyLayout->setContentsMargins(0, 0, 0, 0);
        tabSpells->setLayout(spellsDummyLayout);

        auto spellsScroller = new QScrollArea();
        spellsScroller->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        spellsScroller->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        spellsScroller->setWidgetResizable(true);
        spellsScroller->setContentsMargins(0, 0, 0, 0);
        spellsDummyLayout->addWidget(spellsScroller);

        auto *spellsMainWidget = new QWidget();
        spellsMainWidget->setContentsMargins(0, 0, 0, 0);
        spellsScroller->setWidget(spellsMainWidget);

        auto spellsMainLayout = new QVBoxLayout();
        spellsMainWidget->setLayout(spellsMainLayout);

        for (int i = 0 ; i < 5; ++i)
        {
            std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(spellsMainLayout, "Level " + std::to_string(i));
        }

        // Resists tab
        auto tabResists = new QWidget();
        tabs->addTab(tabResists, "Resists");

        auto resistsMainLayout = new QGridLayout();
        tabResists->setLayout(resistsMainLayout);

        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(resistsMainLayout, "Resistance", 0, 0);
        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(resistsMainLayout, "Immunity", 1, 0);
        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(resistsMainLayout, "Weakness", 0, 1);
        std::ignore = AddGroupBoxWithLayout<QHBoxLayout>(resistsMainLayout, "Inversion", 1, 1);

        // Class tab
        auto tabClass = new QWidget();
        tabs->addTab(tabClass, "Class"); // and level(s) and background and species

        auto *classLayout = new QVBoxLayout();
        tabClass->setLayout(classLayout);

        auto classCharacterLayout = AddGroupBoxWithLayout<QGridLayout>(classLayout, "Character");

        AddNumberField(classCharacterLayout, "Species", 0, 0);
        AddNumberField(classCharacterLayout, "Background", 0, 2);
        AddNumberField(classCharacterLayout, "Alignment", 0, 4);

        auto classClassLayout = AddGroupBoxWithLayout<QGridLayout>(classLayout, "Classes");

        AddNumberField(classClassLayout, "Class", 0, 0);
        AddNumberField(classClassLayout, "Subclass", 0, 2);
        AddNumberField(classClassLayout, "Level", 0, 4);
        AddNumberField(classClassLayout, "Class", 1, 0);
        AddNumberField(classClassLayout, "Subclass", 1, 2);
        AddNumberField(classClassLayout, "Level", 1, 4);

        // Lore tab
        auto tabLore = new QWidget();
        tabs->addTab(tabLore, "Lore");
    }

private:
    QVBoxLayout *topLayout = nullptr;

    std::string name;

    template <typename BoxLayoutType, typename ParentLayoutType, typename ...Args>
    requires (std::derived_from<BoxLayoutType, QLayout>, std::derived_from<ParentLayoutType, QLayout>)
    BoxLayoutType* AddGroupBoxWithLayout(ParentLayoutType *target, const std::string &name, Args&& ...addWidgetArgs)
    {
        auto box = new QGroupBox(QString::fromStdString(name));
        target->addWidget(box, std::forward<Args>(addWidgetArgs)...);

        auto layout = new BoxLayoutType();
        layout->setAlignment(Qt::AlignCenter);
        box->setLayout(layout);
        return layout;
    }

    void AddNumberField(QGridLayout *target, const std::string &name, int row, int col)
    {
        auto label = new QLabel(QString::fromStdString(name + ":"));
        target->addWidget(label, row, col, Qt::AlignLeft);

        auto *lineEdit = new QLineEdit();
        lineEdit->setReadOnly(true);
        lineEdit->setValidator(new QIntValidator(std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max()));
        lineEdit->setMinimumWidth(50);
        lineEdit->setMaximumWidth(50);
        target->addWidget(lineEdit, row, col + 1, Qt::AlignLeft);
    }
};
