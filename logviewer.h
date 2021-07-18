//
// Created by mortie on 18.07.21.
//

#ifndef LOGVIEWER_LOGVIEWER_H
#define LOGVIEWER_LOGVIEWER_H

#include <QWidget>

class QStandardItemModel;

namespace Ui{
    class LogViewerForm;
}

class LogViewer : public QWidget
{
    Q_OBJECT

public:
    enum LogType{
        Alert,
        Messages,
        Network,
        Error
    };
    explicit LogViewer(QWidget *parent = nullptr);

private slots:
    void logSelectorsChanged();
    void on_firstBtn_clicked();
    void on_previousBtn_clicked();
    void on_nextBtn_clicked();
    void on_lastBtn_clicked();

private:
    Ui::LogViewerForm *ui;

    QStringList logList;

    QStandardItemModel *m_model;
    QList<LogType> m_selectedLogTypes;

    void populateModel();
    QColor determineLogColor(LogType type);
    void readLogFile();
};

#endif //LOGVIEWER_LOGVIEWER_H
