#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class ocdraw : public QObject
{
    Q_OBJECT

public:
    ocdraw();
    ~ocdraw();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

ocdraw::ocdraw()
{

}

ocdraw::~ocdraw()
{

}

void ocdraw::initTestCase()
{

}

void ocdraw::cleanupTestCase()
{

}

void ocdraw::test_case1()
{

}

QTEST_MAIN(ocdraw)

#include "tst_ocdraw.moc"
