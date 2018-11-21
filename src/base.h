#ifndef BASE_H
#define BASE_H

class Base {
    public:
        /* Constructors */
        Base() { };

        /* Pure Virtual Functions */
        virtual bool execute() = 0;
	virtual void print_args() = 0;
};

#endif

