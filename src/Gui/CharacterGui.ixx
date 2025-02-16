module;

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>

#include <unordered_set>
#include <string>
#include <limits>

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
        resize(800, 600);
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

        auto statsFluidBox = new QGroupBox("Status");
        statsTopLayout->addWidget(statsFluidBox, 0, 0);

        auto statsFluidLayout = new QGridLayout();
        statsFluidBox->setLayout(statsFluidLayout);

        AddNumberField(statsFluidLayout, "Current HP", 0, 0);
        AddNumberField(statsFluidLayout, "Max HP", 0, 2);
        AddNumberField(statsFluidLayout, "Temp HP", 0, 4);
        AddNumberField(statsFluidLayout, "Conditions", 0, 6);

        auto statsMiscBox = new QGroupBox("Misc");
        statsTopLayout->addWidget(statsMiscBox, 1, 0);

        auto statsMiscLayout = new QGridLayout();
        statsMiscBox->setLayout(statsMiscLayout);

        AddNumberField(statsMiscLayout, "Armor Class", 0, 0);
        AddNumberField(statsMiscLayout, "Speed", 0, 2);
        AddNumberField(statsMiscLayout, "Proficiency Bonus", 0, 4);
        AddNumberField(statsMiscLayout, "Passive Perception", 0, 6);

        auto statsBottomLayout = new QHBoxLayout();
        statsMainLayout->addLayout(statsBottomLayout);

        auto primaryStatsBox = new QGroupBox("Primary Stats");
        statsBottomLayout->addWidget(primaryStatsBox);

        auto primaryStatsLayout = new QGridLayout();
        primaryStatsBox->setLayout(primaryStatsLayout);

        for (const std::string &s : DefaultPrimaryStats)
            AddNumberField(primaryStatsLayout, s, primaryStatsLayout->rowCount(), 0);

        auto primarySavesBox = new QGroupBox("Saving Throws");
        statsBottomLayout->addWidget(primarySavesBox);

        auto primarySavesLayout = new QGridLayout();
        primarySavesBox->setLayout(primarySavesLayout);

        for (const std::string &s : DefaultPrimaryStats)
            AddNumberField(primarySavesLayout, s, primarySavesLayout->rowCount(), 0);

        auto skillsBox = new QGroupBox("Skills");
        statsBottomLayout->addWidget(skillsBox);

        auto skillsLayout = new QGridLayout();
        skillsBox->setLayout(skillsLayout);

        AddNumberField(skillsLayout, "Cat Handling", 0, 0);
        AddNumberField(skillsLayout, "TODO all the normal stuff", 1, 0);

        // Actions tab
        auto tabActions = new QWidget();
        tabs->addTab(tabActions, "Actions");

        auto actionsMainLayout = new QGridLayout();
        tabActions->setLayout(actionsMainLayout);

        auto actionsActionsBox = new QGroupBox("Actions");
        actionsMainLayout->addWidget(actionsActionsBox, 0, 0, 2, 1);

        auto actionsBonusActionsBox = new QGroupBox("Bonus Actions");
        actionsMainLayout->addWidget(actionsBonusActionsBox, 0, 1);

        auto actionsReactionsBox = new QGroupBox("Reactions");
        actionsMainLayout->addWidget(actionsReactionsBox, 1, 1);

        // Abilities tab
        auto tabAbilities = new QWidget();
        tabs->addTab(tabAbilities, "Abilities");

        auto abilitiesMainLayout = new QGridLayout();
        tabAbilities->setLayout(abilitiesMainLayout);

        auto abilitiesPassiveBox = new QGroupBox("Passive");
        abilitiesMainLayout->addWidget(abilitiesPassiveBox, 0, 0);

        auto abilitiesProficiencies = new QGroupBox("Proficiencies");
        abilitiesMainLayout->addWidget(abilitiesProficiencies, 0, 1);

        // Items tab
        auto tabItems = new QWidget();
        tabs->addTab(tabItems, "Items");

        auto itemsMainLayout = new QGridLayout();
        tabItems->setLayout(itemsMainLayout);

        auto itemsEquippedBox = new QGroupBox("Equipped");
        itemsMainLayout->addWidget(itemsEquippedBox, 0, 0);

        auto itemsCurrencyBox = new QGroupBox("Currency");
        itemsMainLayout->addWidget(itemsCurrencyBox, 1, 0);

        auto itemsInventoryBox = new QGroupBox("Inventory");
        itemsMainLayout->addWidget(itemsInventoryBox, 0, 1, 2, 1);

        // Spells tab
        auto tabSpells = new QWidget();
        tabs->addTab(tabSpells, "Spells");

        // Class tab
        auto tabClass = new QWidget();
        tabs->addTab(tabClass, "Class"); // and level

        // Lore tab
        auto tabLore = new QWidget();
        tabs->addTab(tabLore, "Lore");
    }

private:
    QVBoxLayout *topLayout = nullptr;

    std::string name;

    void AddNumberField(QGridLayout *target, const std::string &name, int row, int col)
    {
        auto label = new QLabel(QString::fromStdString(name + ":"));
        label->setAlignment(Qt::AlignRight);
        target->addWidget(label, row, col);

        auto *lineEdit = new QLineEdit();
        lineEdit->setReadOnly(true);
        lineEdit->setValidator(new QIntValidator(std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max()));
        lineEdit->setAlignment(Qt::AlignLeft);
        lineEdit->setMinimumWidth(50);
        lineEdit->setMaximumWidth(50);
        target->addWidget(lineEdit, row, col + 1);
    }
};
