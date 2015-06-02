#ifndef WIPELOGIC_H
#define WIPELOGIC_H

#include <QDeclarativeItem>
#include <QObject>

namespace mblsft {
namespace wipe
{


class WipeLogic : public QObject
{
    Q_OBJECT

    Q_PROPERTY( int platformFlag READ getPlatformFlag NOTIFY platformFlagChanged )

public:
    explicit WipeLogic(QObject *parent = 0);
    ~WipeLogic();

signals:
    void platformFlagChanged();

public slots:
    int getPlatformFlag();
    int getFontPointSizeM();
    int getFontPointSizeM2();
    int getFontPointSizeL();


private:
    int mPlatformFlag;
};


}
}

#endif // WIPELOGIC_H
