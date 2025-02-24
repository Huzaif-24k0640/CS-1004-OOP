#include <iostream>
using namespace std;

class MusicPlayer {
private:
    string playlist[50];   
    int totalSongs;
    string currentlyPlayingSong;

public:
    MusicPlayer() : totalSongs(0), currentlyPlayingSong("") {
        cout << "Music Player Initialized. Add some songs to your playlist!\n";
    }

    void addSong(string songName) {
        if (totalSongs < 50) {
            playlist[totalSongs++] = songName;
            cout << "Song '" << songName << "' added to the playlist.\n";
        } else {
            cout << "Playlist is full! Cannot add more songs.\n";
        }
    }

    void removeSong(string songName) {
        for (int i = 0; i < totalSongs; i++) {
            if (playlist[i] == songName) {
                cout << "Removing song: " << songName << " from the playlist.\n";
                for (int j = i; j < totalSongs - 1; j++) {
                    playlist[j] = playlist[j + 1];
                }
                totalSongs--;
                return;
            }
        }
        cout << "Song '" << songName << "' not found in the playlist.\n";
    }

    void playSong(string songName) {
        for (int i = 0; i < totalSongs; i++) {
            if (playlist[i] == songName) {
                currentlyPlayingSong = songName;
                cout << "Now Playing: " << currentlyPlayingSong << " \n";
                return;
            }
        }
        cout << "Song '" << songName << "' not found in the playlist.\n";
    }

    void displayPlaylist() {
        cout << "\nPlaylist:\n";
        if (totalSongs == 0) {
            cout << "No songs in the playlist. Add some music!\n";
        } else {
            for (int i = 0; i < totalSongs; i++) {
                cout << i + 1 << ". " << playlist[i] << endl;
            }
        }
    }
};

int main() {
    MusicPlayer imranPlayer;

    imranPlayer.addSong("Shape of You");
    imranPlayer.addSong("Blinding Lights");
    imranPlayer.addSong("Someone Like You");
    imranPlayer.addSong("Perfect");

    imranPlayer.displayPlaylist();

    imranPlayer.playSong("Blinding Lights");

    imranPlayer.removeSong("Shape of You");

    imranPlayer.displayPlaylist();

    imranPlayer.playSong("Shape of You");

    return 0;
}
