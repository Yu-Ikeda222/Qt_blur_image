#include "processimage.h"
#include "processimage.h"
#include <QImage>
#include <mainwindow.h>

ProcessImage::ProcessImage(QObject *parent)
    : QObject{parent}
{
}

void ProcessImage::process_image() {
    QImage* image = process_data.dst;
    int size = process_data.size;
    long long progress_total =  (*image).height() * (*image).width() * 4 * (size * 2 + 1) * (size * 2 + 1) - 1;
    long long progress_counter = 0;

    for ( int row = 0; row < (*image).height(); row++ ) {
        for ( int col = 0; col < (*image).width(); col++ )
        {
            int progress_status = (int)(((long double)(progress_counter) / (long double)(progress_total)) * 100);
            emit image_process(progress_status);
            int rr, cc;
            int r = 0;
            int g = 0;
            int b = 0;
            int color_counter = 0;
            for (rr = row - size; rr <= row + size; rr++)  {
                for (cc = col - size; cc <= col + size; cc++) {
                    if(rr >= 0 && rr <= (*image).height() && cc >= 0 && cc <= (*image).width()) {
                        QRgb color = (*image).pixel(cc,rr);
                        r += qRed(color);
                        g += qGreen(color);
                        b += qBlue(color);
                        color_counter++;
                    }
                }
                progress_counter++;
            }
            (*image).setPixel(col,row, qRgb(r / color_counter, g / color_counter, b / color_counter));
        }
    }

}

void ProcessImage::get_image_data(data data) {
    process_data = data;
    process_image();
}



