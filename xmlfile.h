#include <QFile>
#include <QString>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QVector>

#ifndef XMLFILE_H
#define XMLFILE_H


class XmlFile {
public:
    XmlFile(); //Constructor
    XmlFile(QString xmlfilename); //Constructor
    void setFile(QString newfile); //Changes xml source file name(CREATES NEW)
    QVector<QString> getList(); //returns the cscientists vector read from XML TODO:CLASSify
    void update(QVector<QString> newVector); //Update list and write to file
private:
    void writeToFile(); //writes cscientists to XML file
    void createNewFile(); //Creates a new xml file if there isn't a corresponding one
    void checkFile(); //Does the file exist?
    void readFile(); //Reads XML file
    QString filename; //filename of xml file
    QFile file; //file instance
    QXmlStreamWriter xmlwriter; //QXml library writer
    QXmlStreamReader xmlreader; //QXml library reader
    QVector<QString> cscientists; //The scientists read from XML -- this needs to be changed to scientist class
};

#endif // XMLFILE_H
