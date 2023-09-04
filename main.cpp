#include "http.h"
#include "pk2sprite_repository.h"
#include <iostream>

int main(int argc, char**argv)
{
    //Change this according to your PK2 sprites directory location
    std::string sprites_path = "/mnt/Elephant/games/pk2/res/sprites";

    //or define environment variable PK2_SPRITE_PATH.
    if(const char* env_p = std::getenv("PK2_SPRITE_PATH")){
        sprites_path = env_p;
    }

    std::cout<<"PK2 Sprite directory: "<<sprites_path<<std::endl;
    
    std::string address = "0.0.0.0";
    int port = 8080;

    {
        int arg_parsing_state=0;
        for(int i=0;i<argc;++i){
            std::string arg = argv[i];
            switch (arg_parsing_state)
            {
            case 0:{
                if(arg=="-h"||arg=="--help"){
                    std::cout<<"PK2 Web Sprite editor backend\n";
                    std::cout<<"-p/--port <port> \t -> select port, default: 8080\n";
                    std::cout<<"-a/--address <address> \t -> select address to listen, default \"0.0.0.0\"\n";
                    std::cout<<"-s/--sprite_path <path> \t -> select sprite path\n";

                    return 0;
                }
                else if(arg=="-p"||arg=="--port"){
                    arg_parsing_state = 1;
                }
                else if(arg=="-a"||arg=="--address"){
                    arg_parsing_state = 2;
                }
            }
            break;
            case 1:{
                arg_parsing_state = 0;
                port = std::stoi(arg);
            }
            break;
            case 2:{
                arg_parsing_state = 0;
                address = arg;
            }

            default:
                break;
            }
        }
    }

    std::cout<<"Loading sprites..."<<std::endl;
    kogutozaurus::PK2SpriteRepository repo(sprites_path);


    httplib::Server svr;
    svr.Get("/hi", [](const httplib::Request &, httplib::Response &res)
    {
        res.set_content("Hello World!", "text/plain");
    });

    repo.addRoutes(svr);

    std::cout<<"Server listening on "<<address<<":"<<port<<std::endl;
    svr.listen(address.c_str(), port);

    return 0;
}