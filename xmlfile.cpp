#include "xmlfile.h"

//========CONSTRUCTORS==========
XmlFile::XmlFile()
{
    filename = "";

    order_by = "NAME";
    view_gender = "BOTH";
}

XmlFile::XmlFile(QString xmlfilename)
{
    setFile(xmlfilename);

    order_by = "NAME";
    view_gender = "BOTH";
}

//========PUBLIC FUNCTIONS==========
void XmlFile::setFile(QString newfile)
{
    filename = newfile + ".xml";
    file.setFileName(filename);
    xmlwriter.setDevice(&file);
    xmlreader.setDevice(&file);

    readFile();
}


QVector<Person> XmlFile::getList()
{
    return cscientists;
}

QString XmlFile::getOrdering()
{
    return order_by;
}

QString XmlFile::getViewGender()
{
    return view_gender;
}

void XmlFile::update(QVector<Person> newVector, QString _order_by, QString _view_gender)
{
    cscientists = newVector;
    order_by = _order_by;
    view_gender = _view_gender;
    writeToFile();
}

//========PRIVATE FUNCTIONS==========
void XmlFile::writeToFile() //Writes the vector to file
{
    file.open(QIODevice::WriteOnly);

    xmlwriter.setAutoFormatting(true);
    xmlwriter.writeStartDocument();

    xmlwriter.writeStartElement("programdata");

    xmlwriter.writeStartElement("scientists");
    for(int i = 0; i < cscientists.size(); i++)
    {
        xmlwriter.writeStartElement("scientist");
        xmlwriter.writeTextElement("name", cscientists[i].getName());
        xmlwriter.writeTextElement("gender", cscientists[i].getGender());
        xmlwriter.writeTextElement("dob", cscientists[i].getDoB());
        xmlwriter.writeTextElement("dod", cscientists[i].getDoD());
        xmlwriter.writeEndElement();
    }
    xmlwriter.writeEndElement();

    xmlwriter.writeStartElement("settings");
    xmlwriter.writeTextElement("order_by", order_by);
    xmlwriter.writeTextElement("view_gender", view_gender);
    xmlwriter.writeEndElement();

    xmlwriter.writeEndElement();

    file.close();
}

void XmlFile::readFile()
{
    if(!file.exists())
    {
        return;
    }
    file.open(QIODevice::ReadOnly);
    xmlreader.setDevice(&file);

    QString tempqstr = "";
    string tempstr = "";
    Person temp;

    xmlreader.readNext();
    while(!xmlreader.atEnd()) //this is super ugly, BUT IT WORKS!. Everything I've tried to clean it up breaks its functionality.. BEWARE
    {
        if(xmlreader.isStartElement())
        {
            // <settings>
            if(xmlreader.name() == "settings")
            {
                xmlreader.readNext();
            }
            else if(xmlreader.name() == "order_by")
            {
                order_by = xmlreader.readElementText();
                xmlreader.readNext();
            }
            else if(xmlreader.name() == "view_gender")
            {
                view_gender = xmlreader.readElementText();
                xmlreader.readNext();
            }
            // </settings>

            // <scientists>
            if(xmlreader.name() == "scientist")
            {
                xmlreader.readNext();
            }
            else if(xmlreader.name() == "name")
            {
                tempqstr = xmlreader.readElementText();
                tempstr = tempqstr.toStdString();
                temp.setName(tempstr);
                xmlreader.readNext();
            }
            else if(xmlreader.name() == "gender")
            {
                tempqstr = xmlreader.readElementText();
                tempstr = tempqstr.toStdString();
                temp.setGender(tempstr);
                xmlreader.readNext();
            }
            else if(xmlreader.name() == "dob")
            {
                tempqstr = xmlreader.readElementText();
                tempstr = tempqstr.toStdString();
                temp.setDoB(tempstr);
                xmlreader.readNext();
            }
            else if(xmlreader.name() == "dod")
            {
                tempqstr = xmlreader.readElementText();
                tempstr = tempqstr.toStdString();
                temp.setDoD(tempstr);
                xmlreader.readNext();
                cscientists.push_back(temp); //this has to be in the last tag within scientist
            }
            //</scientists>
       }
       else if (xmlreader.isEndElement())
       {
           xmlreader.readNext();
       }
       xmlreader.readNext();
    }
    file.close();
}
