#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// Doubly linked list node for a song
struct Song {
    int id;             // song ID
    string title;       // song title
    string artist;      // artist name
    float duration;     // duration in minutes
    Song* prev;         // pointer to previous song
    Song* next;         // pointer to next song
};

Song* front = nullptr;    // first song
Song* tail = nullptr;    // last song
Song* current = nullptr; // current "now playing" pointer

// Load playlist from file into doubly linked list (append to existing list)
void loadPlaylist() {
    ifstream in("playlist.txt");
    if (!in.is_open()) return;

    while (in >> ws && !in.eof()) {
        Song* s = new Song();
        // File format: ID,Title,Artist,Duration
        string idStr, durationStr;
        getline(in, idStr, ',');
        if (idStr.empty()) { delete s; break; }
        s->id = stoi(idStr);
        getline(in, s->title, ',');
        getline(in, s->artist, ',');
        getline(in, durationStr);
        s->duration = stof(durationStr);

        s->prev = tail;
        s->next = nullptr;

        if (!front) front = s;
        else tail->next = s;
        tail = s;
        if (!current) current = front;
    }
    in.close();
}

// Save entire playlist to file (overwrite)
void savePlaylist() {
    ofstream out("playlist.txt");
    Song* temp = front;
    while (temp) {
        out << temp->id << ","
            << temp->title << ","
            << temp->artist << ","
            << fixed << setprecision(2) << temp->duration << endl;
        temp = temp->next;
    }
    out.close();
}

// Add a new song at the tail
void addSong() {
    Song* s = new Song();
    cout << "Enter Song ID: ";
    cin >> s->id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Title: ";
    getline(cin, s->title);

    cout << "Enter Artist: ";
    getline(cin, s->artist);

    cout << "Enter Duration (in minutes): ";
    cin >> s->duration;

    s->prev = tail;
    s->next = nullptr;

    if (!front) front = s;
    else tail->next = s;
    tail = s;

    if (!current) current = front;

    cout << "Song added to playlist!\n";
}

// Display playlist from head to tail
void displayPlaylist() {
    if (!head) { cout << "Playlist is empty.\n"; return; }
    cout << "\nCURRENT PLAYLIST\n";
    cout << left << setw(6) << "ID"
        << setw(24) << "Title"
        << setw(22) << "Artist"
        << setw(8) << "Duration" << endl;

    Song* temp = front;
    while (temp) {
        cout << left << setw(6) << temp->id
            << setw(24) << temp->title
            << setw(22) << temp->artist
            << setw(8) << fixed << setprecision(2) << temp->duration << endl;
        temp = temp->next;
    }
}

// Move current to next song
void playNext() {
    if (!current) { cout << "Playlist is empty.\n"; return; }
    if (!current->next) {
        cout << "You are at the last song.\n";
        return;
    }
    current = current->next;
    cout << "Now playing: " << current->title << " by " << current->artist
        << " (" << fixed << setprecision(2) << current->duration << " min)\n";
}

// Move current to previous song
void playPrevious() {
    if (!current) { cout << "Playlist is empty.\n"; return; }
    if (!current->prev) {
        cout << "You are at the first song.\n";
        return;
    }
    current = current->prev;
    cout << "Now playing: " << current->title << " by " << current->artist
        << " (" << fixed << setprecision(2) << current->duration << " min)\n";
}

// Remove a song by ID, and adjust head/tail/current pointers safely
void removeSong() {
    if (!head) { cout << "Playlist is empty.\n"; return; }

    int targetId;
    cout << "Enter Song ID to remove: ";
    cin >> targetId;

    Song* temp = front;
    while (temp) {
        if (temp->id == targetId) {
            // Relink neighbors
            if (temp->prev) temp->prev->next = temp->next;
            else front = temp->next;

            if (temp->next) temp->next->prev = temp->prev;
            else tail = temp->prev;

            // Move current if it points to the deleted node
            if (current == temp) {
                current = temp->next ? temp->next : temp->prev;
            }

            cout << "Song '" << temp->title << "' removed from playlist.\n";
            delete temp;
            return;
        }
        temp = temp->next;
    }
    cout << "Song not found.\n";
}

int p2() {
    loadPlaylist();
    int choice;

    cout << "****** Welcome to Music Playlist Manager ******\n";
    do {
        cout << "\n1. Add Song to Playlist\n2. Display Playlist\n3. Play Next Song\n4. Play Previous Song\n5. Remove Song\n6. Save and Exit\n> ";
        cin >> choice;

        switch (choice) {
        case 1: addSong(); break;
        case 2: displayPlaylist(); break;
        case 3: playNext(); break;
        case 4: playPrevious(); break;
        case 5: removeSong(); break;
        case 6: savePlaylist(); cout << "Playlist saved. See you next jam!\n"; break;
        default: cout << "Invalid option. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}