#ifndef EVENTGENERATOR_H
#define EVENTGENERATOR_H

#include <QObject>

class EventGenerator : public QObject
{
    Q_OBJECT
public:
    explicit EventGenerator(QObject *parent = 0);

    static void keyPressDownArrow();
    static void keyPressUpArrow();

signals:

public slots:

   private:
    static void generateKeypressEvent(int code);

};

#endif // EVENTGENERATOR_H
