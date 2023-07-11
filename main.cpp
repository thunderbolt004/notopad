#include <cstdlib>
#include <unordered_map>
#include "Account.h"
#include "files.h"

sf::RenderWindow window;
std::string user = "", passwd = "";
std::string s1= "", prompt = "Welcome back, Manu";
// prompt[0] = "Username: ";

bool ctrl = false, lshift = false, rshift = false;
bool taking_username = true, taking_password = true;
int font_size = 24, chars;
int lshift_count = 0;

std::string bg_images_parent_folder = "bg_images/";
std::string fonts_parent_folder = "fonts/";
std::string curr_font = fonts_parent_folder.append("Ubuntu-L.ttf");
std::string bg_image = bg_images_parent_folder.append(bg_images[rand() % (bg_images.size())]);

std::map<std::string, Account*> USERS;
void makeAccount(std::string username, std::string passwd);

int main(int argc, char const *argv[]){
    sf::RenderWindow window(sf::VideoMode(720, 405), "Manu's Diary");
    srand(time(0));
    if(USERS.find(user) == USERS.end()){
        user = argv[1], passwd = argv[2];
        makeAccount(user, passwd);
    }
    if(passwd != USERS[user]->getPass()){
        exit(-1);
    }
    prompt = "Welcome Back, " + user;
    sf::String printed = prompt + "\n";
    while (window.isOpen()){
        sf::Event event;
        chars = printed.getSize();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed){
                switch(event.key.code){
                    case sf::Keyboard::RControl : ctrl = true; break;
                    case sf::Keyboard::LControl : ctrl = true; break;
                    case sf::Keyboard::RShift : rshift = true; break;
                    case sf::Keyboard::LShift : {
                        lshift = true;
                        if(chars > prompt.size()){
                            printed.erase(chars-1, 1);
                        }
                    }; break;
                }

                if(ctrl){
                    switch(event.key.code){
                        case sf::Keyboard::Q : window.close() ; break;
                        case sf::Keyboard::S : USERS[user]->newEntry(printed, prompt.size()); break;
                        case sf::Keyboard::D : USERS[user]->showEntry(); break;
                        case sf::Keyboard::Up : ++font_size; break;
                        case sf::Keyboard::Down : --font_size; break;
                        case sf::Keyboard::Slash : {
                            fonts_parent_folder = "fonts/";
                            curr_font = fonts_parent_folder.append(fonts[rand() % (fonts.size())]);
                       }; break;
                   }
               }
               else if(event.key.code == sf::Keyboard::Up && rshift){
                    bg_images_parent_folder = "bg_images/";
                    bg_image = bg_images_parent_folder.append(bg_images[rand() % (bg_images.size())]);
                }

                if(event.key.code == sf::Keyboard::Enter){
                    printed += "\n";
                }
            }

            if (event.type == sf::Event::TextEntered && !ctrl){
                printed += char(event.text.unicode);
            }
            if(event.type == sf::Event::KeyReleased){
                switch(event.key.code){
                    case sf::Keyboard::RControl : ctrl = false; break;
                    case sf::Keyboard::LControl : ctrl = false; break;
                    case sf::Keyboard::LShift : {
                        lshift = false;
                        lshift_count = 0;
                    }; break;
                }
            }
        }

        /******setting background image******/
        sf::Texture texture;
        texture.loadFromFile(bg_image);
        sf::Sprite sprite;
        sprite.setTexture(texture);
        window.draw(sprite);
        /********done setting image********/

        /******setting text******/
        sf::Font font;
        font.loadFromFile(curr_font);
        sf::Text text;
        text.setFont(font);

        if(lshift){
            ++lshift_count;
        }

        /******backspaces******/
        if(ctrl && lshift_count == 10){
            if(chars > prompt.size()){
                printed.erase(chars-1, 1);
            }
            lshift_count = 0;
        }
        if(lshift_count == 30){
            if(chars > prompt.size()){
                printed.erase(chars-1, 1);
            }
            lshift_count = 0;
        }
        /**********************/
        
        text.setString(printed);
        text.setCharacterSize(font_size);
        text.setFillColor(sf::Color::White);
        window.draw(text);
        /*****done setting text*****/

        window.display();
    }
    return 0;
}

void makeAccount(std::string username = "", std::string passwd = ""){
    if(username == ""){
        std::cout<<"\nEnter Username: ";
        std::cin>>username;
    }
    if(passwd == ""){
        std::cout<<"\nEnter -Strong- Password: ";
        std::cin>>passwd;
    }
    USERS[username] = new Account(username, passwd);
    std::ofstream acc;
    acc.open(username, std::ios::binary);
    std::hash<std::string> hasher;
    size_t pass_hash = hasher(passwd);
    acc<<pass_hash<<std::endl;
    acc.close();
}