#include <iostream>
#include <dlfcn.h>
#include "Bin.h"
#include "Ter.h"

typedef char *(*FunctionPointer)(long x);

int main()
{
    void *lib = dlopen("./libBin.so", RTLD_LAZY);
    if (!lib)
    {
        std::cout << "Error with opening lib: " << dlerror() << "\n";
        return 1;
    }
    FunctionPointer translate = reinterpret_cast<FunctionPointer>(dlsym(lib, "translate"));

    if (!translate)
    {
        std::cout << "Error with toBinary pointer: " << dlerror() << "\n";
    }

    std::cout << "Enter number and it will be translate to other notation" << std::endl;
    std::cout << "Notations: Binary Ternary" << std::endl;
    std::cout << "Enter 0 to change notation (default - Binary)" << std::endl;
    bool flag = false;
    long x;
    while (1)
    {
        std::cout << "Enter x" << std::endl;
        std::cin >> x;
        if (std::cin.fail())
        {
            std::cout << "Incorrect value" << std::endl;
            return 1;
        }
        if (x == 0)
        {
            if (flag == false)
            {
                dlclose(lib);
                lib = dlopen("./libTer.so", RTLD_LAZY);
                if (!lib)
                {
                    std::cout << "Error with opening lib: " << dlerror() << "\n";
                    return 1;
                }
                translate = reinterpret_cast<FunctionPointer>(dlsym(lib, "translate"));

                if (!translate)
                {
                    std::cout << "Error with toTernary pointer: " << dlerror() << "\n";
                }
                std::cout << "Changed notation to ternary" << std::endl;
            }
            else if (flag == true)
            {
                dlclose(lib);
                lib = dlopen("./libBin.so", RTLD_LAZY);
                if (!lib)
                {
                    std::cout << "Error with opening lib: " << dlerror() << "\n";
                    return 1;
                }
                translate = reinterpret_cast<FunctionPointer>(dlsym(lib, "translate"));

                if (!translate)
                {
                    std::cout << "Error with toTernary pointer: " << dlerror() << "\n";
                }
                std::cout << "Changed notation to binary" << std::endl;
            }

            flag = !flag;
            continue;
        }
        else
        {
            char *res = translate(x);
            std::cout << "Result: " << res << std::endl;
            delete[] res;
        }
    }

    dlclose(lib);
}