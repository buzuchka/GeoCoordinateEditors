#ifndef FORMAT_H
#define FORMAT_H

class QString;

class DegreeCoordinateEditor;

class AbstractFormat
{
public:
    AbstractFormat(DegreeCoordinateEditor * edit);
    virtual ~AbstractFormat();

    virtual void setValue(double decimalDegrees) = 0;

    virtual QString getDisplayValue() const = 0;
    virtual int getDisplayWidth() const = 0;

    virtual void setMaxDegrees(int maxDegreesValue){}

protected:
    DegreeCoordinateEditor *const m_edit;
};

class Format_DDMMSS : public AbstractFormat
{
public:
    Format_DDMMSS(DegreeCoordinateEditor * edit);
    ~Format_DDMMSS();

    void setValue(double decimalDegrees);

    QString getDisplayValue() const;
    int getDisplayWidth() const;

    void setMaxDegrees(int maxDegreesValue);

private:
    double m_degrees;
    double m_minutes;
    double m_seconds;

    int m_maxDegrees;
    const int m_maxMinutes;
    const int m_maxSeconds;

    int m_degreesFieldLength;
    int m_minutesFieldLength;
    int m_secondsFieldLength;
};

#endif
