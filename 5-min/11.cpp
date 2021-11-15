#include <iostream>

enum class MediaPlayer_ID {MidiPlayer = 0, MP3Player};

class MediaPlayer{
public:    
    virtual void play();
};

class PlayerFactory{
public:
    bool registerPlayer(MediaPlayer * player, int i);
    static MediaPlayer * getPlayer(MediaPlayer_ID); 
};

class MidiPlayer: public MediaPlayer{
    void play() override{
        std::cout << "MidiPlayer" << std::endl;
    }
};

class MP3Player: public MediaPlayer{    
    void play() override{
        std::cout << "MP3Player" << std::endl;
    }
};

MediaPlayer* PlayerFactory::getPlayer(MediaPlayer_ID id){
    MediaPlayer* a;
    if(id == MediaPlayer_ID::MP3Player){
        a = new MP3Player();
        return a;
    }
    else if(id == MediaPlayer_ID::MP3Player){
        a = new MP3Player();
        return a;
    }
    else{
        std::cerr << "no such instance";
        return nullptr;
    }
}

int main(){
    MediaPlayer* mp3 = PlayerFactory::getPlayer(MediaPlayer_ID::MP3Player);
    MediaPlayer* midi = PlayerFactory::getPlayer(MediaPlayer_ID::MidiPlayer);
    //MediaPlayer* midi = PlayerFactory::getPlayer(MediaPlayer_ID::dsabj);
}

/*
1. создайте базовый класс MediaPlayer. Этот класс должен иметь виртуальную функцию void play()
2. создайте двух наследников MediaPlayer: MidiPlayer и MP3Player. Каждый из них должен перегружать
   метод play и печатать в консоль какое-нибудь сообщение
3. создайте класс PlayerFactory, в котором будут методы: 
    - bool registerPlayer(MediaPlayer * player, int i)
    - MediaPlayer * getPlayer(int)
   не забудьте сделать этот класс синглтоном (как мы делали с getInstance)
4. сделайте регистрацию MidiPlayer и MP3Player с помощью объявления глобальных переменных
   в анонимном нэймспейсе (как делали на семинаре)
5. напишите метод main, который парсит из входных аргументов целое число и пытается создать
   и запустить плеер который зарегистрирован с тем же числом. если не находит такой плеер, то печатает ошибку.
   Плееры должны искаться с помощью методов фабрики.
Подсказка: сразу объявляйте каждый класс в отдельном хэдере
Подсказка2: не забудьте include guard'ы
*/