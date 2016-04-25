#ifndef __MTOOLS_H__
#define __MTOOLS_H__

/* for example when you want the name of an object. or any other variable.*/
#define GETNAME(X) #X
/* this is for when you want to "use" a variable to silence the unused errors.*/
#define UNUSED(X) (void)(X)

#endif