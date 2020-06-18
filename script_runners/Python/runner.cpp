#include <stdio.h>
#include <mach-o/dyld.h>
#include <CoreServices/CoreServices.h>
#include <Python/Python.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <assert.h>
#include <pthread.h>

extern "C" __attribute__ ((visibility("default"))) void* DoSomething(void *data)
{
    char cmd []= "PYTHON CODE HERE";
    setlocale(LC_ALL, "en_US.URF-8");
    Py_Initialize();
    PyRun_SimpleString(cmd);
    
    Py_Finalize();
    return 0;
}

__attribute__ ((constructor)) void run()
{
    pthread_attr_t  attr;
    pthread_t       posixThreadID;
    int             returnVal;
    
    returnVal = pthread_attr_init(&attr);
    assert(!returnVal);
    returnVal = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    assert(!returnVal);
    
    int threadError = pthread_create(&posixThreadID, &attr, &DoSomething, NULL);
}
