#include <QtTest>

// add necessary includes here

class RevoluteParserTest : public QObject
{
    Q_OBJECT

public:
    RevoluteParserTest();
    ~RevoluteParserTest();

private slots:
    void test_case1();

};

RevoluteParserTest::RevoluteParserTest()
{

}

RevoluteParserTest::~RevoluteParserTest()
{

}

void RevoluteParserTest::test_case1()
{

}

QTEST_MAIN(RevoluteParserTest)

#include "tst_revolute_parser.moc"
