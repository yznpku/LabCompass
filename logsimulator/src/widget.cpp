#include "widget.h"
#include "ui_widget.h"

Widget::Widget(Settings* settings, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    this->settings = settings;
    ui->setupUi(this);
    ui->roomTable->setColumnCount(3);
    ui->roomTable->setHorizontalHeaderLabels({ "ID", "Name", "Area Code" });
    ui->roomTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->roomTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->roomTable->verticalHeader()->setVisible(false);
    ui->roomTable->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->clientPathEdit->setText(settings->get_poeClientPath());

    connect(ui->mapBrowseButton, &QPushButton::clicked,
        [this]() {
            auto fileName = QFileDialog::getOpenFileName(this, "Open File", this->settings->get_importDirectory(), "Maps (*.json *.map)");
            if (!fileName.isEmpty())
                loadMapFile(fileName);
        });

    connect(ui->goButton, &QPushButton::clicked,
        [this]() {
            auto selection = ui->roomTable->selectionModel();
            if (!selection->hasSelection())
                return;

            auto row = selection->currentIndex().row();
            auto roomName = ui->roomTable->item(row, 1)->text();
            emit roomChanged(roomName);
        });

    connect(ui->startButton, &QPushButton::clicked,
        [this]() { emit labStarted(); });

    connect(ui->izaroStartButton, &QPushButton::clicked,
        [this]() { emit izaroBattleStarted(); });

    connect(ui->finishSectionButton, &QPushButton::clicked,
        [this]() { emit sectionFinished(); });

    connect(ui->finishButton, &QPushButton::clicked,
        [this]() { emit labFinished(); });

    connect(ui->plazaButton, &QPushButton::clicked,
        [this]() { emit roomChanged("Aspirants\' Plaza"); });

    connect(ui->hideoutButton, &QPushButton::clicked,
        [this]() { emit roomChanged("Coastal Hideout"); });

    connect(ui->invalidRoomButton, &QPushButton::clicked,
        [this]() { emit roomChanged("Estate Annex"); });
}

Widget::~Widget()
{
    delete ui;
}

QString Widget::getClientPath() const
{
    return ui->clientPathEdit->text();
}

QString Widget::getClientId() const
{
    if (ui->clientId1Button->isChecked())
        return "001";
    else if (ui->clientId2Button->isChecked())
        return "002";
    return "000";
}

void Widget::loadMapFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return;

    auto json = QJsonDocument::fromJson(file.readAll()).object();
    auto rooms = json["rooms"].toArray();

    ui->mapNameLabel->setText(json["date"].toString() + ' ' + json["difficulty"].toString());

    ui->roomTable->clearContents();
    ui->roomTable->setRowCount(rooms.size());

    for (int i = 0; i < rooms.size(); i++) {
        QJsonObject room = rooms[i].toObject();
        auto id = room["id"].toString();
        auto name = room["name"].toString();
        auto areaCode = room["areacode"].toString();

        auto parts = name.split(' ');
        for (int i = 0; i < parts.size(); i++)
            parts[i].replace(0, 1, parts[i][0].toUpper());
        name = parts.join(" ");

        auto idItem = new QTableWidgetItem(id);
        idItem->setFlags(idItem->flags() ^ Qt::ItemIsEditable);
        ui->roomTable->setItem(i, 0, idItem);

        auto nameItem = new QTableWidgetItem(name);
        nameItem->setFlags(nameItem->flags() ^ Qt::ItemIsEditable);
        ui->roomTable->setItem(i, 1, nameItem);

        auto areaCodeItem = new QTableWidgetItem(areaCode);
        areaCodeItem->setFlags(areaCodeItem->flags() ^ Qt::ItemIsEditable);
        ui->roomTable->setItem(i, 2, areaCodeItem);
    }
}
