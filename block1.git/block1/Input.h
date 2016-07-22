#ifndef _INPUT_H_
#define _INPUT_H_

class Input
{
public:
    enum _TYPE_ : unsigned int
    {
        TYPE_DOWN = 0,
        TYPE_UP      ,
        TYPE_REP     ,
        TYPE_COUNT
    };
    enum _KEY_ : int
    {
        KEY_LEFT  = 1,
        KEY_UP    = 2,
        KEY_RIGHT = 4,
        KEY_DOWN  = 8
    };

    Input();
    virtual ~Input();

    virtual void reset();
    virtual void reflectKeyUp();

    virtual void keyDown(const unsigned int dependencyKey);
    virtual void keyRepeat(const unsigned int dependencyKey);
    virtual void keyUp(const unsigned int dependencyKey);

    virtual bool isDown(const unsigned int key) const;
    virtual bool isRepeat(const unsigned int key) const;
    virtual bool isUp(const unsigned int key) const;

private:
    unsigned char _flags[TYPE_COUNT];

    static unsigned int _dependencyKey2key(const unsigned int dependencyKey);

};

#endif // _INPUT_H_
