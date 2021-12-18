#ifndef PROCESSIMAGE_H
#define PROCESSIMAGE_H

#include <QObject>

class ProcessImage : public QObject
{
    Q_OBJECT
public:
    explicit ProcessImage(QObject *parent = nullptr);
    struct data
    {
        QImage *dst;
        int size;
    };
    void process_image();
    data process_data;

public slots:
    void get_image_data(data);

signals:
    void image_process(int);

};

#endif // PROCESSIMAGE_H
