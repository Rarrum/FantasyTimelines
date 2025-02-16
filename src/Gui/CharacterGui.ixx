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

        tabs = new QTabWidget();

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

        tabs = new QTabWidget();
        topLayout->addWidget(tabs);

        // Stats tab
        tabStats = new QWidget();
        tabs->addTab(tabStats, "Stats");

        statsMainLayout = new QVBoxLayout();
        tabStats->setLayout(statsMainLayout);

        statsTopLayout = new QGridLayout();
        statsMainLayout->addLayout(statsTopLayout);

        AddNumberField(statsTopLayout, "Current HP", 0, 0); //TODO group boxes for health and misc?
        AddNumberField(statsTopLayout, "Max HP", 0, 2);
        AddNumberField(statsTopLayout, "Temp HP", 0, 4);
        AddNumberField(statsTopLayout, "Armor Class", 0, 6);
        AddNumberField(statsTopLayout, "Speed", 0, 8);

        statsBottomLayout = new QHBoxLayout();
        statsMainLayout->addLayout(statsBottomLayout);

        primaryStatsBox = new QGroupBox();
        primaryStatsBox->setTitle("Primary Stats");
        statsBottomLayout->addWidget(primaryStatsBox);

        primaryStatsLayout = new QGridLayout();
        primaryStatsBox->setLayout(primaryStatsLayout);

        for (const std::string &s : DefaultPrimaryStats)
            AddNumberField(primaryStatsLayout, s, primaryStatsLayout->rowCount(), 0);

        primaryStatsLayout->addItem(new QSpacerItem(10, 20), primaryStatsLayout->rowCount(), 0);

        AddNumberField(primaryStatsLayout, "Proficiency Bonus", primaryStatsLayout->rowCount(), 0);
        AddNumberField(primaryStatsLayout, "Passive Perception", primaryStatsLayout->rowCount(), 0);

        primarySavesBox = new QGroupBox();
        primarySavesBox->setTitle("Saving Throws");
        statsBottomLayout->addWidget(primarySavesBox);

        primarySavesLayout = new QGridLayout();
        primarySavesBox->setLayout(primarySavesLayout);

        for (const std::string &s : DefaultPrimaryStats)
            AddNumberField(primarySavesLayout, s, primarySavesLayout->rowCount(), 0);

        skillsBox = new QGroupBox();
        skillsBox->setTitle("Skills");
        statsBottomLayout->addWidget(skillsBox);

        skillsLayout = new QGridLayout();
        skillsBox->setLayout(skillsLayout);

        AddNumberField(skillsLayout, "Cat Handling", 0, 0);
        AddNumberField(skillsLayout, "TODO all the normal stuff", 1, 0);

        //TODO: where to put proficiencies?

        // Items tab
        tabItems = new QWidget();
        tabs->addTab(tabItems, "Items");

        itemsMainLayout = new QGridLayout();
        tabItems->setLayout(itemsMainLayout);

        itemsEquippedBox = new QGroupBox();
        itemsEquippedBox->setTitle("Equipped");
        itemsMainLayout->addWidget(itemsEquippedBox, 0, 0);

        itemsCurrencyBox = new QGroupBox();
        itemsCurrencyBox->setTitle("Currency");
        itemsMainLayout->addWidget(itemsCurrencyBox, 1, 0);

        itemsInventoryBox = new QGroupBox();
        itemsInventoryBox->setTitle("Inventory");
        itemsMainLayout->addWidget(itemsInventoryBox, 0, 1, 2, 1);

        // Abilities tab
        tabAbilities = new QWidget();
        tabs->addTab(tabAbilities, "Abilities");

        abilitiesMainLayout = new QGridLayout();
        tabAbilities->setLayout(abilitiesMainLayout);

        abilitiesActionsBox = new QGroupBox();
        abilitiesActionsBox->setTitle("Actions");
        abilitiesMainLayout->addWidget(abilitiesActionsBox, 0, 0);

        abilitiesBonusActionsBox = new QGroupBox();
        abilitiesBonusActionsBox->setTitle("Bonus Actions");
        abilitiesMainLayout->addWidget(abilitiesBonusActionsBox, 0, 1);

        abilitiesReactionsBox = new QGroupBox();
        abilitiesReactionsBox->setTitle("Reactions");
        abilitiesMainLayout->addWidget(abilitiesReactionsBox, 1, 0);

        abilitiesPassiveBox = new QGroupBox();
        abilitiesPassiveBox->setTitle("Passive");
        abilitiesMainLayout->addWidget(abilitiesPassiveBox, 1, 1);

        // Spells tab
        tabSpells = new QWidget();
        tabs->addTab(tabSpells, "Spells");

        // Class tab
        tabClass = new QWidget();
        tabs->addTab(tabClass, "Class"); // and level

        // Lore tab
        tabLore = new QWidget();
        tabs->addTab(tabLore, "Lore");
    }

private:
    QVBoxLayout *topLayout = nullptr;
    QTabWidget *tabs = nullptr;

    QWidget *tabStats = nullptr;
    QVBoxLayout *statsMainLayout = nullptr; //TODO just use QGridLayout
    QGridLayout *statsTopLayout = nullptr;
    QHBoxLayout *statsBottomLayout = nullptr;
    QGroupBox *primaryStatsBox = nullptr;
    QGridLayout *primaryStatsLayout = nullptr;
    QGroupBox *primarySavesBox = nullptr;
    QGridLayout *primarySavesLayout = nullptr;
    QGroupBox *skillsBox = nullptr;
    QGridLayout *skillsLayout = nullptr;

    QWidget *tabItems = nullptr;
    QGridLayout *itemsMainLayout = nullptr;
    QGroupBox *itemsEquippedBox = nullptr;
    QGroupBox *itemsCurrencyBox = nullptr;
    QGroupBox *itemsInventoryBox = nullptr;

    QWidget *tabAbilities = nullptr;
    QGridLayout *abilitiesMainLayout = nullptr;
    QGroupBox *abilitiesActionsBox = nullptr;
    QGroupBox *abilitiesBonusActionsBox = nullptr;
    QGroupBox *abilitiesReactionsBox = nullptr;
    QGroupBox *abilitiesPassiveBox = nullptr;

    QWidget *tabSpells = nullptr;
    QWidget *tabClass = nullptr;
    QWidget *tabLore = nullptr;

    std::string name;

    void AddNumberField(QGridLayout *target, const std::string &name, int row, int col)
    {
        target->addWidget(new QLabel(QString::fromStdString(name + ":")), row, col);
        QLineEdit *lineEdit = new QLineEdit();
        lineEdit->setReadOnly(true);
        lineEdit->setValidator(new QIntValidator(std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max()));
        target->addWidget(lineEdit, row, col + 1);
    }
};
