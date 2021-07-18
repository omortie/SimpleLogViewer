//
// Created by mortie on 18.07.21.
//

#include "logviewer.h"
#include "ui_logviewer.h"

#include <QStandardItemModel>
#include <QFile>
#include <QMessageBox>

LogViewer::LogViewer(QWidget *parent)
        : QWidget(parent)
        , ui(new Ui::LogViewerForm)
{
    ui->setupUi(this);

    // allocating model
    m_model = new QStandardItemModel(this);
    readLogFile();
    ui->logView->setModel(m_model);

    // connect log selector buttons signals
    connect(ui->alertBtn, &QToolButton::toggled, this, &LogViewer::logSelectorsChanged);
    connect(ui->messagesBtn, &QToolButton::toggled, this, &LogViewer::logSelectorsChanged);
    connect(ui->networkBtn, &QToolButton::toggled, this, &LogViewer::logSelectorsChanged);
    connect(ui->errorBtn, &QToolButton::toggled, this, &LogViewer::logSelectorsChanged);
    logSelectorsChanged();
}

void LogViewer::populateModel() {
    m_model->clear();

    if (logList.isEmpty()) {
        return;
    }

            foreach(const auto &log, logList) {
            if (log.isEmpty()) {
                continue;;
            }

            QStringList logRow = log.split(",");
            QString LogText = logRow.takeFirst();
            LogType logType = static_cast<LogType>(logRow.takeFirst().toInt());

            auto logItem = new QStandardItem(LogText);
            logItem->setEditable(false);
            logItem->setData(logType);
            logItem->setData(determineLogColor(logType),Qt::BackgroundRole);

            // add the log to the model based on current log type selectors
            if (m_selectedLogTypes.contains(logType)) {
                m_model->appendRow(logItem);
            }
        }
}

void LogViewer::readLogFile() {
    // try to open the log file to read from
    QFile logFile("logs.txt");
    if (!logFile.open(QIODevice::ReadOnly)) {
        // show error if unable to read
        QMessageBox::warning(this, tr("Read Failed"),
                             tr("Reading logs from file has been failed"));
    }

    // read the logs and parse them to a log map
    QString logContent = logFile.readAll();
    logList = logContent.split("\n");
}

QColor LogViewer::determineLogColor(LogType type) {
    QColor resultColor;
    switch (type) {
        case Alert:
            resultColor = QColor("lime");
            break;
        case Messages:
            resultColor = QColor("cyan");
            break;
        case Network:
            resultColor = QColor("blue");
            break;
        case Error:
            resultColor = QColor("red");
            break;
    }

    return resultColor;
}

void LogViewer::logSelectorsChanged() {
    // clear pre-selected log types
    m_selectedLogTypes.clear();

    // populate selected log types again based on user selection
    if (ui->alertBtn->isChecked()) {
        m_selectedLogTypes.append(Alert);
    }
    if (ui->messagesBtn->isChecked()) {
        m_selectedLogTypes.append(Messages);
    }
    if (ui->networkBtn->isChecked()) {
        m_selectedLogTypes.append(Network);
    }
    if (ui->errorBtn->isChecked()) {
        m_selectedLogTypes.append(Error);
    }

    populateModel();
}

void LogViewer::on_firstBtn_clicked() {
    ui->logView->setCurrentIndex(m_model->index(0, 0));
}

void LogViewer::on_previousBtn_clicked() {
    if (ui->logView->currentIndex().row() == 0) {
        return;
    }

    ui->logView->setCurrentIndex(m_model->index(ui->logView->currentIndex().row() - 1, 0));
}

void LogViewer::on_nextBtn_clicked() {
    if (ui->logView->currentIndex().row() == m_model->rowCount() - 1) {
        return;
    }
    ui->logView->setCurrentIndex(m_model->index(ui->logView->currentIndex().row() + 1, 0));
}

void LogViewer::on_lastBtn_clicked() {
    ui->logView->setCurrentIndex(m_model->index(m_model->rowCount() - 1, 0));
}
