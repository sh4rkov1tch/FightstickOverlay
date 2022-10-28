#include <CApp.hpp>

int main(int argc, char **argv){

    if(!argv[1])
        CApp theApp;
    else
        CApp theApp(argv[1]);

    return EXIT_SUCCESS;
}