#include <iostream>
#include <cstdio> 
#include <string>
#include "raylib.h"
#include <cstring>
#include <ctime>
#include<fstream>
using namespace std;


#define MAX_INPUT_CHARS 30
#define MAX_CODE_LEN 10

class EmailVerificationPage {
    private:
        string userEmail;
        char codeInput[MAX_CODE_LEN + 1] = "";
        int codeLen = 0;
    
        Rectangle codeBox, verifyBtn;
        string realCode;
        string feedback;
    public:
        bool order = false; 
        bool login = false;
        bool verified = false;
        bool codeSent = false;
        bool codeInvalid = false;
        EmailVerificationPage() {
            codeBox = { 270, 250, 260, 30 };
            verifyBtn = { 310, 310, 180, 35 };
        }
    
        string GenerateCode() {
            srand(time(0));
            int code = rand() % 9000 + 1000;
            return to_string(code);
        }
    
        void SendCode() {
            if(login) realCode = "ALERT";
            else if(order) realCode = "ORDER";
            else {
            realCode = GenerateCode();
            }
            string command = "python run_email.py " + string(userEmail) + " " + realCode + "";
            int result = system(command.c_str());
            if (result == 0) {
                feedback = "Code sent to your email.";
                codeSent = true;
            } else {
                feedback = "Failed to send email.";
                codeInvalid = true;
            }
        }
    
        void getEmail(string email){
            userEmail = email;
            SendCode();
        }
    
        void Update() {
            Vector2 mouse = GetMousePosition();
    
            if ( CheckCollisionPointRec(mouse, verifyBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (strcmp(codeInput, realCode.c_str()) == 0) {
                        verified = true;
                        feedback = "Email verified!";
                    } else {
                        feedback = "Incorrect code.";
                    }
                
            }
    
            int key = GetCharPressed();
            while (key > 0 && codeLen < MAX_CODE_LEN) {
                if (key >= '0' && key <= '9') {
                    codeInput[codeLen++] = (char)key;
                    codeInput[codeLen] = '\0';
                }
                key = GetCharPressed();
            }
    
            if (IsKeyPressed(KEY_BACKSPACE) && codeLen > 0) {
                codeInput[--codeLen] = '\0';
            }
        }
        void DrawBackgroundGradient(int w, int h) {
            for (int y = 0; y < h; y++) {
                DrawLine(0, y, w, y, (Color){100 + y / 10, 200 + y / 20, 220, 255});
            }
        }
        void Draw() {
            
            DrawText("Email Verification", 280, 180, 22, DARKBLUE);
    
            DrawText("Enter 4-digit Code", codeBox.x, codeBox.y - 20, 12, GRAY);
            DrawRectangleRec(codeBox, LIGHTGRAY);
            DrawText(codeInput, codeBox.x + 10, codeBox.y + 8, 20, BLACK);
    
            DrawRectangleRec(verifyBtn, GREEN);
            DrawText("Verify Code", verifyBtn.x + 40, verifyBtn.y + 8, 14, WHITE);
    
            if (!feedback.empty()) {
                DrawText(feedback.c_str(), 270, 370, 14, (verified ? DARKGREEN : RED));
            }
        }
    
        void Run() {
            if (!codeSent) SendCode();
            Update();
            DrawBackgroundGradient(800,600);
            Draw();
    
        }
    
        bool IsVerified() { return verified; }
};

class order{
    private:
    string HouseNo;
    string street;
    int price;
    string date;
    public:
    order& operator=(const order& other) {
        if (this != &other) { 
            HouseNo = other.HouseNo;
            street = other.street;
            price = other.price;
            date = other.date;
        }
        return *this;
    }
    order(){
        dateFind();
    }
    void setPrice(int p){
        price = p;
    }
    void setHouse(string h){
        HouseNo = h;
    }
    void setStreet(string s){
        street = s;
    }
    void dateFind(){
        time_t now = time(nullptr);
        tm* local_time = localtime(&now);
        char buffer[11];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", local_time);
        date = buffer;
    }
    int getPrice(){
        return price;
    }
    string getDate(){
        return date;
    }
    string getHouse(){
        return HouseNo;
    }
    string getstreet(){
        return street;
    }
    string serialize()  {
        
        return HouseNo + "," + street + "," + to_string(price) + "," + date;
    }
    void deserialize(const string& data) {
        size_t p1 = data.find(',');
        size_t p2 = data.find(',', p1 + 1);
        size_t p3 = data.find(',', p2 + 1);
        HouseNo = data.substr(0, p1);
        street = data.substr(p1 + 1, p2 - p1 - 1);
        price = stoi(data.substr(p2 + 1, p3 - p2 - 1));
        date = data.substr(p3 + 1);
    }
    ~order(){}
};

class User {
    private:
        string password;
    public:
        order Order[3];
        string username;
        void Register(string uname, string pass) {
            username = uname;
            password = pass;
        }
        void getorder(order o){
            for (int i = 1; i < 3; ++i) {
                Order[i-1] = Order[i];
            }
            Order[2] = o;
        }
        string getEmail(){
            return username;
        }
    
        bool IsRegistered() const {
            return !username.empty() && !password.empty();
        }
        friend void storeOrder(User &user);
        friend void storeInFile(User &user);
        friend bool FindInfile(User &user);
        friend bool FindEmail(User &user);
        friend void changepassword(User &user);
        
    };
    
    bool FindEmail(User &user) {
        ifstream in("UserRecord.txt");
        if (!in.is_open()) {
            cerr << "File not found!" << endl;
            return false;
        }
        string line;
        bool flag = false;  
        while (getline(in, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string uname = line.substr(0, pos);
                if (user.username == uname) {
                    flag = true;
                    break; 
                }
            }
        }
    
        in.close();
        return flag;
    }
    
    void storeOrder(User &user) {
        ifstream in("UserRecord.txt");
        ofstream out("Sample.txt");
    
        string line;
        while (getline(in, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string uname = line.substr(0, pos);
                if (uname == user.username) {
                    out << user.username << ":" << user.password;
                    for (int i = 0; i < 3; ++i) {
                        if (user.Order[i].getHouse() != "") {
                            out << "|" << user.Order[i].serialize();
                        }
                    }
                    out << "\n";
                } else {
                    out << line << "\n"; 
                }
            }
        }
    
        in.close();
        out.close();
        remove("UserRecord.txt");
        rename("Sample.txt", "UserRecord.txt");
    }
    void changepassword(User &user){
        ifstream in("UserRecord.txt");
        ofstream out("Sample.txt");

        string line;
        while (getline(in, line)) {
            size_t pos = line.find(':');
            if (pos == string::npos) continue;

            string uname = line.substr(0, pos);
            string rest = line.substr(pos + 1);  

            if (uname == user.username) {
                size_t orderStart = rest.find('|');
                if (orderStart != string::npos) {
                    out << user.username << ":" << user.password << rest.substr(orderStart) << "\n";
                } else {
                    out << user.username << ":" << user.password << "\n";
                }
            } else {
                out << line << "\n";
            }
    }

    in.close();
    out.close();
    remove("UserRecord.txt");
    rename("Sample.txt", "UserRecord.txt");
    }
    
    
    void storeInFile(User &user){
        ofstream out("UserRecord.txt", ios::app);
        out << user.username << ":" << user.password << "\n";
        out.close();
    }
bool FindInfile(User& user) {
    ifstream in("UserRecord.txt");
    string line;

    while (getline(in, line)) {
        size_t pos = line.find(':');
        if (pos == string::npos) continue;

        string uname = line.substr(0, pos);
        string rest = line.substr(pos + 1);
        size_t nextPipe = rest.find('|');
        string pass = (nextPipe == string::npos) ? rest : rest.substr(0, nextPipe);

        if (uname == user.username && pass == user.password) {
            int idx = 0;
            size_t current = nextPipe;

            while (current != string::npos && idx < 3) {
                size_t next = rest.find('|', current + 1);
                string data;
                if (next == string::npos) {
                    data = rest.substr(current + 1);
                } else {
                    data = rest.substr(current + 1, next - current - 1);
                }

                if (!data.empty()) {
                    user.Order[idx].deserialize(data);
                    idx++;
                }
                current = next;
            }

            in.close();
            return true; 
        }
    }

    in.close();
    return false;
}

bool IsValidEmail(char* email) {
    char* at = strchr(email, '@');
    if (!at) return false;

    char* dot = strchr(at, '.');
    if (!dot || dot <= at + 1) return false;

    return true;
}

class InputField {
public:
    int letterCount = 0;
    char text[MAX_INPUT_CHARS + 1] = "";
    bool isActive = false;

    friend void UpdateInputField(InputField& field);
};

void UpdateInputField(InputField& field) {
    int key = GetCharPressed();

    while (key > 0) {
        if ((key >= 32) && (key <= 125) && (field.letterCount < MAX_INPUT_CHARS)) {
            field.text[field.letterCount] = (char)key;
            field.text[field.letterCount + 1] = '\0';
            field.letterCount++;
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && field.letterCount > 0) {
        field.letterCount--;
        field.text[field.letterCount] = '\0';
    }
}

class History{
    private:
    Rectangle card;
    User user;
    Rectangle backButton;
    public:
    bool stop;
    History(){
        stop = false;
        card = {100, 40, 800 - 200, 600 - 80};
        backButton = {295,480,200,40};
    }
    void DrawBackgroundGradient() {
        for (int y = 0; y < 600; y++) {
            DrawLine(0, y, 800, y, (Color){100 + y / 10, 200 + y / 20, 220, 255});
        }
    }
    void draw() {
        DrawRectangleRounded(card, 0.05f, 10, WHITE);
        DrawRectangleLinesEx(card, 2, LIGHTGRAY);

        for (int i = 0; i < 3; ++i) {
            float y_offset = card.y + 30 + i * 130;

            DrawText(TextFormat("ORDER %d", i + 1), card.x + 240, y_offset + 10, 20, DARKGRAY);

            DrawText("House No:", card.x + 20, y_offset + 30, 15, GRAY);
            DrawText(user.Order[i].getHouse().c_str(), card.x + 110, y_offset + 30, 15, BLACK);

            DrawText("Street:", card.x + 350, y_offset + 30, 15, GRAY);
            DrawText(user.Order[i].getstreet().c_str(), card.x + 420, y_offset + 30, 15, BLACK);

            DrawText("Price:", card.x + 20, y_offset + 65, 15, GRAY);
            DrawText(TextFormat("%d", user.Order[i].getPrice()), card.x + 110, y_offset + 65, 15, BLACK);

            DrawText("Date:", card.x + 350, y_offset + 65, 15, GRAY);
            DrawText(user.Order[i].getDate().c_str(), card.x + 420, y_offset + 65, 15, BLACK);

            DrawText("Status:", card.x + 220, y_offset + 100, 15, GRAY);
            DrawText("Completed", card.x + 280, y_offset + 100, 15, RED);

            if (i < 2) {
                DrawLine(card.x + 10, y_offset + 130, card.x + card.width - 10, y_offset + 130, LIGHTGRAY);
            }
        }

        DrawRectangleRec(backButton,Fade(RED,0.0f));
        DrawText("BACK", backButton.x + 70, backButton.y + 10,20,GRAY);
    }
    void HandleInput(){
        Vector2 mousePoint = GetMousePosition();
        if(CheckCollisionPointRec(mousePoint,backButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            stop = true;
        }
    }
    void getUser(User u){
        user = u;
    }
    void Start(){
        DrawBackgroundGradient();
        draw();
        HandleInput();
    }
    bool getStop(){
        return stop;
    }

};

class ForgetPassword{
    private:
    Rectangle back;
    InputField forgetUsername;
    InputField forgetPassword;
    InputField forgetcomfrim;
    Rectangle forgetEmail;
    Rectangle forgetpass;
    Rectangle forgetcomf;
    string feedbackMessage;
    EmailVerificationPage email;
    Rectangle actionButton;
    bool menu = false;
    public:
    bool changed = false;
    bool BACK = false;
    User storedUser3;
    ForgetPassword(){
        back = {50 , 50, 240, 30};
        forgetEmail = {280 , 260, 240 , 30};
        forgetpass = {280, 310 , 240, 30};
        forgetcomf = {280 , 360, 240, 30};
        actionButton = { 280, 410, 240, 35 };
    }
    void DrawBackgroundGradient(int w, int h) {
        for (int y = 0; y < h; y++) {
            DrawLine(0, y, w, y, (Color){100 + y / 10, 200 + y / 20, 220, 255});
        }
    }
    void Handle(){
        Vector2 mousePoint = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            forgetUsername.isActive = CheckCollisionPointRec(mousePoint, forgetEmail);
            forgetPassword.isActive = CheckCollisionPointRec(mousePoint, forgetpass);
            forgetcomfrim.isActive = CheckCollisionPointRec(mousePoint, forgetcomf);
        }

        if (forgetUsername.isActive) UpdateInputField(forgetUsername);
        if (forgetPassword.isActive) UpdateInputField(forgetPassword);
        if (forgetcomfrim.isActive) UpdateInputField(forgetcomfrim);

        if (CheckCollisionPointRec(mousePoint, actionButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            storedUser3.username = forgetUsername.text;
            if (!IsValidEmail(forgetUsername.text)) {
                feedbackMessage = "Invalid email format!";
                return;
            }
            if (strcmp(forgetPassword.text, forgetcomfrim.text) != 0) {
                feedbackMessage = "Passwords do not match!";
                return ;
            }
            storedUser3.Register(forgetUsername.text , forgetPassword.text);
            if (FindEmail(storedUser3)) {
                cout << "Verification sent to email";
                email.getEmail(storedUser3.getEmail());
                menu = true;
            } else {
                feedbackMessage = "Email not found";
            }
        }
        if(CheckCollisionPointRec(mousePoint , back) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            BACK = true;
        }
    }
    void draw(){
            DrawRectangleRec(back , Fade(RED,0.0f));
            DrawText("<-" , back.x , back.y , 40 , WHITE);
            DrawRectangle(250, 150, 300, 350, RAYWHITE);
            DrawText("Change Password", 265, 205, 30, BLACK);

            DrawText("Email Address", forgetEmail.x, forgetEmail.y - 15, 10, GRAY);
            DrawRectangleRec(forgetEmail, (Color){230, 240, 255, 255});
            DrawText(forgetUsername.text, forgetEmail.x + 5, forgetEmail.y + 8, 12, BLACK);

            DrawText("Password", forgetpass.x, forgetpass.y - 15, 10, GRAY);
            DrawRectangleRec(forgetpass, (Color){230, 240, 255, 255});
            DrawText(forgetPassword.text, forgetpass.x + 5, forgetpass.y + 8, 12, BLACK);

            DrawText("Confirm Password", forgetcomf.x, forgetcomf.y - 15, 10, GRAY);
            DrawRectangleRec(forgetcomf, (Color){230, 240, 255, 255});
            DrawText(forgetcomfrim.text, forgetcomf.x + 5, forgetcomf.y + 8, 12, BLACK);

            DrawRectangleRec(actionButton, (Color){0, 170, 200, 255});
            DrawText("RESET", actionButton.x + 90, actionButton.y + 10, 14, WHITE);

            if (!feedbackMessage.empty() && !menu) {
            DrawText(feedbackMessage.c_str(), 280, 460, 12, RED);
            }
        
    }
    void start(){
        DrawBackgroundGradient(800,600);
        if (menu) {
            email.Run();
            if (email.IsVerified()) {
                changepassword(storedUser3);
                feedbackMessage = "Password changed!";
                menu = false; 
                changed = true;
            }
        } else {
            Handle();
            draw();
        }
    }
};

class LoginForm {
private:
    ForgetPassword forgetpassword;
    EmailVerificationPage email;
    bool signIN;
    User storedUser;
    User storedUser2;
    InputField username;
    InputField password;
    InputField newUsername;
    InputField newPassword;
    InputField comfrimPassword;
    Rectangle emailBox;
    Rectangle passBox;
    Rectangle confirmBox;
    Rectangle actionButton;
    Rectangle loginTab;
    Rectangle signupTab;
    Rectangle forgetbox;
    Rectangle notSign;

    string feedbackMessage;

public:
    bool menu;
    bool forget;
    bool EMAIL;

    LoginForm() {
        forgetbox = {280 , 340, 240 ,30 };
        notSign = {280 , 380, 240 ,30};
        forget = false;
        menu = false;
        signIN = false;
        EMAIL = false;
        feedbackMessage = "";
        emailBox = { 280, 260, 240, 30 };
        passBox = { 280, 310, 240, 30 };
        confirmBox = { 280, 360, 240, 30 };
        actionButton = { 280, 410, 240, 35 };
        loginTab = { 260, 210, 140, 30 };
        signupTab = { 410, 210, 130, 30 };
    }

    void HandleInput() {
        Vector2 mousePoint = GetMousePosition();
        if (CheckCollisionPointRec(mousePoint, signupTab) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            signIN = true;
            forget = false;
            feedbackMessage = "";
        }
        if (CheckCollisionPointRec(mousePoint, loginTab) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            signIN = false;
            forget = false;
            feedbackMessage = "";
        }
        if (!signIN) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                username.isActive = CheckCollisionPointRec(mousePoint, emailBox);
                password.isActive = CheckCollisionPointRec(mousePoint, passBox);
            }
    
            if (username.isActive) UpdateInputField(username);
            if (password.isActive) UpdateInputField(password);
    
            if (CheckCollisionPointRec(mousePoint, actionButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                storedUser2.Register(username.text, password.text);
                if (FindInfile(storedUser2)) {
                    email.login = true;
                    email.getEmail(storedUser2.getEmail());
                    menu = true;
                    feedbackMessage = "Login successful!";
                } else {
                    feedbackMessage = "Invalid email or password.";
                }
            }
    
            if (CheckCollisionPointRec(mousePoint, forgetbox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                forget = true;
                feedbackMessage = "";
            }
            if(CheckCollisionPointRec(mousePoint, notSign) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                signIN = true;
            }
        }
        else {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                newUsername.isActive = CheckCollisionPointRec(mousePoint, emailBox);
                newPassword.isActive = CheckCollisionPointRec(mousePoint, passBox);
                comfrimPassword.isActive = CheckCollisionPointRec(mousePoint, confirmBox);
            }
    
            if (newUsername.isActive) UpdateInputField(newUsername);
            if (newPassword.isActive) UpdateInputField(newPassword);
            if (comfrimPassword.isActive) UpdateInputField(comfrimPassword);
    
            if (CheckCollisionPointRec(mousePoint, actionButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (!IsValidEmail(newUsername.text)) {
                    feedbackMessage = "Invalid email format!";
                    return;
                }
                if (strcmp(newPassword.text, comfrimPassword.text) != 0) {
                    feedbackMessage = "Passwords do not match!";
                    return;
                }
                storedUser.Register(newUsername.text, newPassword.text);
                email.getEmail(storedUser.getEmail());
                EMAIL = true;
            }
        }
    }
    User getUser(){
        return storedUser2;
    }

    void DrawBackgroundGradient(int w, int h) {
        for (int y = 0; y < h; y++) {
            DrawLine(0, y, w, y, (Color){100 + y / 10, 200 + y / 20, 220, 255});
        }
    }

    void DrawScreen() {
        if (!signIN && !EMAIL && !forget) {
            DrawRectangle(250, 150, 300, 300, RAYWHITE);
            DrawText("Login Form", 330, 170, 20, (Color){30, 30, 60, 255});

            DrawRectangleRec(loginTab, (Color){0, 150, 200, 255});
            DrawText("Login", 300, 217, 10, WHITE);

            DrawRectangleRec(signupTab, GRAY);
            DrawText("Signup", 445, 217, 10, DARKGRAY);

            DrawText("Email Address", emailBox.x, emailBox.y - 15, 10, GRAY);
            DrawRectangleRec(emailBox, (Color){230, 240, 255, 255});
            DrawText(username.text, emailBox.x + 5, emailBox.y + 8, 12, BLACK);

            DrawText("Password", passBox.x, passBox.y - 15, 10, GRAY);
            DrawRectangleRec(passBox, (Color){230, 240, 255, 255});
            DrawText(password.text, passBox.x + 5, passBox.y + 8, 12, BLACK);

            DrawRectangleRec(forgetbox ,Fade(RED,0.0f));
            DrawText("Forget password?" , forgetbox.x + 8 , forgetbox.y + 20 ,10,(Color){80, 150, 255, 255});

            DrawRectangleRec(notSign , Fade(RED, 0.0f));
            DrawText("Not a member? Signup now", notSign.x + 10,notSign.y, 10, (Color){130, 90, 250, 255});

            DrawRectangleRec(actionButton, (Color){0, 170, 200, 255});
            DrawText("Login", actionButton.x + 90, actionButton.y + 10, 14, WHITE);
        } else if(signIN == true && !EMAIL && !forget ) {

            DrawRectangle(250, 150, 300, 300, RAYWHITE);
            DrawText("Signup Form", 330, 170, 20, (Color){30, 30, 60, 255});

            DrawRectangleRec(loginTab, GRAY);
            DrawText("Login", 300, 217, 10, DARKGRAY);

            DrawRectangleRec(signupTab, (Color){0, 150, 200, 255});
            DrawText("Signup", 445, 217, 10, WHITE);

            DrawText("Email Address", emailBox.x, emailBox.y - 15, 10, GRAY);
            DrawRectangleRec(emailBox, (Color){230, 240, 255, 255});
            DrawText(newUsername.text, emailBox.x + 5, emailBox.y + 8, 12, BLACK);

            DrawText("Password", passBox.x, passBox.y - 15, 10, GRAY);
            DrawRectangleRec(passBox, (Color){230, 240, 255, 255});
            DrawText(newPassword.text, passBox.x + 5, passBox.y + 8, 12, BLACK);

            DrawText("Confirm Password", confirmBox.x, confirmBox.y - 15, 10, GRAY);
            DrawRectangleRec(confirmBox, (Color){230, 240, 255, 255});
            DrawText(comfrimPassword.text, confirmBox.x + 5, confirmBox.y + 8, 12, BLACK);

            DrawRectangleRec(actionButton, (Color){0, 170, 200, 255});
            DrawText("Sign Up", actionButton.x + 90, actionButton.y + 10, 14, WHITE);
        }
        else if((EMAIL == true && !forget) || (EMAIL == true && forget == true)){
            email.Run();
        }
        if (!feedbackMessage.empty() && !EMAIL) {
            DrawText(feedbackMessage.c_str(), 280, 460, 12, RED);
        }
    }

    void start(int width, int height) {
        if(forget == true){
            forgetpassword.start();
            if(forgetpassword.changed){
                forget = false;
                forgetpassword.changed = false;
                feedbackMessage = " Password Changed";
            }
            else if(forgetpassword.BACK){
                forget = false;
                forgetpassword.BACK = false;
            }
        }
        else{
        if (email.IsVerified()) {
                storeInFile(storedUser);
                signIN = false;
                menu = true;
                feedbackMessage = "Signup successful!";
        }
        HandleInput();
        DrawBackgroundGradient(width, height);
        DrawScreen();
        }
    }
};



class orderPage{
    private:
    EmailVerificationPage email;
    InputField house1;
    InputField street1;
    Rectangle Order;
    Rectangle Add;
    Rectangle Subtract;
    Rectangle Add2;
    Rectangle Subtract2;
    Rectangle box;
    Rectangle heading;
    Rectangle HouseNo;
    Rectangle streat;
    Rectangle back; 
    Rectangle PRICE;
    int total;
    int price;
    int quatity;
    order storedOrder;
    User storedUser;
    public:
    bool stop;
    bool isAddClicked;
    bool isSubtractClicked;
    orderPage(){
        isAddClicked = false;
        isSubtractClicked = false;
        stop = false;
        back = {30 ,12 ,240, 30};
        total = 0;
        heading = {10, 10, 780, 40 };
        box = {220 , 70 , 380 , 270};
        HouseNo = { 260 , 130, 300 , 40};
        streat = { 260 , 200 , 300 , 40};
        PRICE = { 300 , 260, 180 , 40};
        Order = {300, 480, 180, 40};
        Add = {120, 350, 180, 40};
        Subtract = {120, 400, 180, 40};
        Add2 = {600, 370 , 80, 40 };
        quatity = 0;
        price = 0;
    }
    void getUser(User  user){
        this-> storedUser = user;
    }
    void setprice(int pr){
        price = pr;
    }
    void DrawBackgroundGradient(){
        DrawRectangleGradientV(0, 0, 800, 600,Color{255, 204, 0, 255}, Color{255, 230, 102, 255});
    }
    void DrawPage(){
        char PriceStr[10];
        sprintf(PriceStr, "%d" , total);
        DrawRectangleRounded(heading , 0.5f, 10,BLACK);
        DrawText("ORDER PAGE", heading.x + 315 , heading.y +10,20 ,WHITE);
        DrawRectangleRec(box ,  Fade(RED,0.0f));
        DrawText("ADDRESS" , box.x + 135, box.y +10, 20 ,BLACK);
        DrawRectangleRec(HouseNo, (Color){230, 240, 255, 255});
        DrawText("HOUSE NO:" , HouseNo.x , HouseNo.y - 20 , 20 ,BLACK);
        DrawText(house1.text,HouseNo.x + 5, HouseNo.y + 8,20,BLACK);
        DrawRectangleRec(streat , (Color){230, 240, 255, 255});
        DrawText("Street" , streat.x , streat.y - 20 ,20,BLACK);
        DrawText(street1.text, streat.x + 5 , streat.y + 8 , 20 ,BLACK);

        DrawRectangleRounded(PRICE, 0.5f, 10, BLACK);
        DrawText("PRICE :  ", PRICE.x + 10 ,PRICE.y + 10 ,18 ,WHITE);
        DrawText(PriceStr, PRICE.x + 80 , PRICE.y + 10,18,WHITE);


        DrawRectangleRounded(Order, 0.5f, 10, BLACK);
        DrawText("Online Order", Order.x  + 40, Order.y + 10, 16, WHITE);

        DrawRectangleRounded(Add, 0.5f, 10, BLACK);
        DrawText("Add Quantity", Add.x + 40, Add.y + 10, 16, WHITE);
        DrawRectangleRounded(Add2, 0.5f, 10, BLACK);
        char quantityStr[10];
        sprintf(quantityStr, "%d", quatity);
        DrawText(quantityStr, Add2.x + 20, Add2.y + 10, 20, WHITE);


        DrawRectangleRounded(Subtract, 0.5f, 10, BLACK);
        DrawText("Remove Quantity", Subtract.x + 40, Subtract.y + 10, 16, WHITE);
        DrawRectangleRec(back , Fade(RED,0.0f));
        DrawText("<-" , back.x , back.y , 40 , WHITE);

    }
    void Handle(){
        Vector2 mousePoint = GetMousePosition();
        if(CheckCollisionPointRec(mousePoint , Add) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
    if (!isAddClicked) {  // Prevent multiple rapid clicks
        quatity += 1;
        total += price;
        isAddClicked = true;  // Set the flag to prevent repeated clicks
    }
}

// Remove Quantity
if(CheckCollisionPointRec(mousePoint , Subtract) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
    if (!isSubtractClicked && quatity > 0) {
        quatity -= 1;
        total -= price;
        isSubtractClicked = true;
    }
}

// Reset the flags when the mouse is released
if (!IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
    isAddClicked = false;
    isSubtractClicked = false;
}
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            house1.isActive = CheckCollisionPointRec(mousePoint, HouseNo);
            street1.isActive = CheckCollisionPointRec(mousePoint, streat);
        }
        if(house1.isActive) UpdateInputField(house1);
        if(street1.isActive) UpdateInputField(street1);

        if(CheckCollisionPointRec(mousePoint, Order) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            if(house1.letterCount > 2 && street1.letterCount > 2 && total > 0){
            storedOrder.setHouse(house1.text);
            storedOrder.setPrice(total);
            storedOrder.setStreet(street1.text);
            storedUser.getorder(storedOrder);
            storeOrder(storedUser); 
            email.order = true;
            email.getEmail(storedUser.getEmail());
            exit (0);
            }
        }
        if(CheckCollisionPointRec(mousePoint, back) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            stop = true;
        }
    }
    void start(){
        Handle();
        DrawBackgroundGradient();
        DrawPage();
    }
};


class burger {
    private:
    Rectangle zingerBurger;
    Rectangle chickenBurger;
    Rectangle zingerBurgerCheese;
    Rectangle veggieBurger;
    Rectangle Back;
    Texture2D texture;
    public:
    bool order;
    orderPage orderUI;
    bool Burger;
    burger(){
        Burger = false;
        texture = LoadTexture("background3.jpg");
        order = false;
        Back = {360,440,240,40};
        zingerBurger = {120, 160, 240, 40};
        chickenBurger = {120, 220, 240, 40};
        zingerBurgerCheese = {120, 280, 240, 40};
        veggieBurger = {120, 340, 240, 40};
        
    }
    void DrawBackgroundGradient() {
        DrawTexture(texture, 0, 0, WHITE);
    }
    void drawBurger(){
        if(order){
            orderUI.start();
        }
        else if(!order){
        DrawRectangleRec(zingerBurger, Fade(RED, 0.0f));
        DrawText("Zinger Burger", zingerBurger.x + 30, zingerBurger.y + 10, 20, WHITE);
        DrawText("450", zingerBurger.x + 500 , zingerBurger.y + 10,20,WHITE);

        DrawRectangleRec(chickenBurger, Fade(RED, 0.0f));
        DrawText("Chicken Burger", chickenBurger.x + 30, chickenBurger.y + 10, 20, WHITE);
        DrawText("350", chickenBurger.x + 500 , chickenBurger.y + 10,20,WHITE);

        DrawRectangleRec(zingerBurgerCheese, Fade(RED, 0.0f));
        DrawText("Zinger Burger Cheese", zingerBurgerCheese.x + 30, zingerBurgerCheese.y + 10, 20, WHITE);
        DrawText("500", zingerBurgerCheese.x + 500 , zingerBurgerCheese.y + 10,20,WHITE);

        DrawRectangleRec(veggieBurger, Fade(RED, 0.0f));
        DrawText("Veggie Burger", veggieBurger.x + 30, veggieBurger.y + 10, 20, WHITE);
        DrawText("250", veggieBurger.x + 500 , veggieBurger.y + 10,20,WHITE);

        DrawRectangleRec(Back, Fade(RED,0.0f));
        DrawText("Back" , Back.x + 20, Back.y + 10, 20, WHITE);
        }
    }
    void handleInput(){
        Vector2 mousePoint = GetMousePosition();
        if (order) {
            orderUI.start();
            if (orderUI.stop) {
                order = false;
                orderUI.stop = false; 
            }
            return; 
        }
        if(CheckCollisionPointRec(mousePoint, zingerBurger) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(450);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, chickenBurger) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(350);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, zingerBurgerCheese) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(500);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, veggieBurger) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(250);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, Back) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            Burger = false;
        }
    }
    void start(){
        handleInput();
        DrawBackgroundGradient();
        drawBurger();
    }
};

class pizza{
    private:
    Rectangle CrownPizza;
    Rectangle TikkaPizza;
    Rectangle Pepperoni;
    Rectangle NewYorkstylepizza;
    Rectangle VeggiePizza;
    Rectangle Back;
    Texture2D texture;
    bool quantity;
    Rectangle small;
    Rectangle Medium;
    Rectangle Large;
    bool crown;
    bool tikka;
    bool pepperoni;
    bool York;
    bool veggie;
    public:
    bool Pizza;
    orderPage orderUI;
    bool order;
    pizza(){
        crown = false;
        tikka = false;
        pepperoni = false;
        York = false;
        veggie = false;
        order = false;
        quantity = false;
        Pizza = false;
        texture = LoadTexture("background3.jpg");
        Back = {360,450,240,40};
        CrownPizza = {120, 150, 240, 40};
        TikkaPizza = {120, 210, 240, 40};
        Pepperoni = {120, 270, 240, 40};
        NewYorkstylepizza= {120, 330, 240, 40};
        VeggiePizza = {120,390 , 240 ,40};
        small = { 280, 230, 240, 40 };
        Medium = { 280, 290, 240, 40 };
        Large = {280, 350, 240, 40};
    }
    void DrawBackgroundGradient() {
        // DrawRectangle(0, 0, w, h, (Color){255, 255, 255, 255}); // White background
        DrawTexture(texture, 0, 0, WHITE);
    }
    void HandleInput(){
        Vector2 mousePoint = GetMousePosition();
        if ( !quantity){
            if(CheckCollisionPointRec(mousePoint, CrownPizza) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                quantity = true;
                crown = true;
            }
            if(CheckCollisionPointRec(mousePoint, TikkaPizza) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                quantity = true;
                tikka = true;
            }
            if (CheckCollisionPointRec(mousePoint, Pepperoni) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                quantity = true;
                pepperoni = true; 
            }
            if (CheckCollisionPointRec(mousePoint, NewYorkstylepizza) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                quantity = true;
                York = true;
            }
            if (CheckCollisionPointRec(mousePoint, VeggiePizza) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                quantity = true;
                veggie = true; 
            }
            if(CheckCollisionPointRec(mousePoint, Back) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                Pizza = false;
            }
        }
        else if(quantity){
            if (order) {
                orderUI.start();
                if (orderUI.stop) {
                    order = false;
                    orderUI.stop = false;
                    quantity = false; 
                }
                return; 
            }
            if(CheckCollisionPointRec(mousePoint, small) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                order = true;
                if(crown)orderUI.setprice(1500);
                else if(tikka)orderUI.setprice(1400);
                else if(York)orderUI.setprice(1500);
                else if(pepperoni)orderUI.setprice(1400);
                else if(veggie)orderUI.setprice(1000);
            }
            if(CheckCollisionPointRec(mousePoint, Medium) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                order = true;
                if(crown)orderUI.setprice(1700);
                else if(tikka)orderUI.setprice(1600);
                else if(York)orderUI.setprice(2000);
                else if(pepperoni)orderUI.setprice(1600);
                else if(veggie)orderUI.setprice(1200);
            }
            if(CheckCollisionPointRec(mousePoint, Large) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                order = true;
                if(crown)orderUI.setprice(2000);
                else if(tikka)orderUI.setprice(1800);
                else if(York)orderUI.setprice(2200);
                else if(pepperoni)orderUI.setprice(1800);
                else if(veggie)orderUI.setprice(1400);
            }
            if(orderUI.stop){
                order = false;
            }
        }
    }
    void DrawPizza(){
        if(quantity == true  && order == false){
        DrawRectangleRec(small, (Color){255, 140, 0, 255});
        DrawRectangleLinesEx(small, 1, DARKGRAY);
        DrawText("Small", small.x + 90, small.y + 10, 20, WHITE);

        DrawRectangleRec(Medium, (Color){200, 30, 60, 255});
        DrawRectangleLinesEx(Medium, 1, DARKGRAY);
        DrawText("Medium", Medium.x + 85, Medium.y + 10, 20, WHITE);

        DrawRectangleRec(Large, (Color){0, 150, 255, 255});
        DrawRectangleLinesEx(Large, 1, DARKGRAY);
        DrawText("Large", Large.x + 85, Large.y + 10, 20, WHITE);
        }

        else if(order == true){
            orderUI.start();
        }

        else if(quantity == false && order == false){
        DrawRectangleRec(CrownPizza , Fade(RED,0.0f));
        DrawText("Crown Pizza",CrownPizza.x +20,CrownPizza.y+10,20,WHITE);
        DrawText("2000" , CrownPizza.x + 500 ,CrownPizza.y + 10 , 20 ,WHITE);
        DrawText("Large", CrownPizza.x + 500, CrownPizza.y - 20 , 20 ,WHITE);
        DrawText("Medium", CrownPizza.x + 410, CrownPizza.y - 20 , 20 ,WHITE);
        DrawText("1700" , CrownPizza.x + 416 , CrownPizza.y + 10 , 20 ,WHITE);
        DrawText("Small", CrownPizza.x + 340, CrownPizza.y - 20 , 20 ,WHITE);
        DrawText("1500" , CrownPizza.x + 346 , CrownPizza.y + 10 , 20 ,WHITE);

        DrawRectangleRec(TikkaPizza, Fade(RED,0.0f));
        DrawText("Tikka Pizza" , TikkaPizza.x + 20 , TikkaPizza.y + 10, 20 , WHITE);
        DrawText("1800" , TikkaPizza.x + 500 ,TikkaPizza.y + 10 ,20 , WHITE);
        DrawText("1400" , TikkaPizza.x + 346 , TikkaPizza.y + 10 , 20 ,WHITE);
        DrawText("1600" , TikkaPizza.x + 416 , TikkaPizza.y + 10 , 20 ,WHITE);

        DrawRectangleRec(Pepperoni , Fade(RED,0.0f));
        DrawText("Pepperoni Pizza" , Pepperoni.x + 20 , Pepperoni.y +10, 20,WHITE);
        DrawText("1800" , Pepperoni.x + 500 ,Pepperoni.y + 10 ,20,WHITE);
        DrawText("1400" , Pepperoni.x + 346 , Pepperoni.y + 10 , 20 ,WHITE);
        DrawText("1600" , Pepperoni.x + 416 , Pepperoni.y + 10 , 20 ,WHITE);

        DrawRectangleRec(NewYorkstylepizza, Fade(RED,0.0f));
        DrawText("New York Pizza" , NewYorkstylepizza.x + 20 , NewYorkstylepizza.y + 10,20,WHITE);
        DrawText("2200" , NewYorkstylepizza.x + 500 , NewYorkstylepizza.y + 10 ,20 ,WHITE);
        DrawText("2000" , NewYorkstylepizza.x + 346 , NewYorkstylepizza.y + 10 , 20 ,WHITE);
        DrawText("1500" , NewYorkstylepizza.x + 416 , NewYorkstylepizza.y + 10 , 20 ,WHITE);

        DrawRectangleRec(VeggiePizza ,Fade(RED,0.0f));
        DrawText("Veggie Pizza" , VeggiePizza.x + 20 ,VeggiePizza.y + 10 ,20, WHITE);
        DrawText("1400" , VeggiePizza.x + 500 , VeggiePizza.y + 10 ,20 ,WHITE);
        DrawText("1200" , VeggiePizza.x + 346 , VeggiePizza.y + 10 , 20 ,WHITE);
        DrawText("1000" , VeggiePizza.x + 416 , VeggiePizza.y + 10 , 20 ,WHITE);
    
        DrawRectangleRec(Back , Fade(RED,0.0f));
        DrawText("Back" , Back.x + 20 , Back.y + 10, 20 ,WHITE);
        }
    }
    void start(){
        HandleInput();
        DrawBackgroundGradient();
        DrawPizza();
    }
};

class Sandwish {
    private:
    Rectangle VegSandwich;
    Rectangle PeriPeri;
    Rectangle ClubSandwich;
    Rectangle PaneerTikka;
    Rectangle MayoChicken;
    Rectangle Back;
    Texture2D texture;
    public:
    bool sandwich;
    orderPage orderUI;
    bool order;
    Sandwish(){
        sandwich = false;
        order = false;
        Back = {360,450,240,40};
        texture = LoadTexture("background3.jpg");
        VegSandwich = {120, 150, 240, 40};
        PeriPeri = {120, 210, 240, 40};
        ClubSandwich = {120, 270, 240, 40};
        PaneerTikka = {120, 330, 240, 40};
        MayoChicken = {120,390 , 240 ,40};
    }
    void DrawBackgroundGradient() {
        DrawTexture(texture, 0, 0, WHITE);
    }
    void DrawSandwich(){
        if(order){
            orderUI.start();
        }
        else if(!order){
        DrawRectangleRec(Back, Fade(RED,0.0f));
        DrawText("Back" , Back.x + 20 ,Back.y + 10, 20,WHITE);

        DrawRectangleRec(VegSandwich , Fade(RED,0.0f));
        DrawText("Veg Sandwich", VegSandwich.x + 20 ,VegSandwich.y + 10, 20,WHITE);
        DrawText("250", VegSandwich.x + 500, VegSandwich.y + 10 , 20 ,WHITE);

        DrawRectangleRec(PeriPeri, Fade(RED,0.0f));
        DrawText("Peri Peri Chicken Sandwich" , PeriPeri.x + 20,PeriPeri.y + 10,20,WHITE);
        DrawText("350" , PeriPeri.x + 500, PeriPeri.y + 10, 20, WHITE);

        DrawRectangleRec(ClubSandwich , Fade(RED,0.0f));
        DrawText("Club Sandwich", ClubSandwich.x + 20, ClubSandwich.y + 10 , 20,WHITE);
        DrawText("300" ,ClubSandwich.x + 500 , ClubSandwich.y + 10,20,WHITE);

        DrawRectangleRec(PaneerTikka , Fade(RED,0.0f));
        DrawText("Paneer Tikka", PaneerTikka.x + 20 ,PaneerTikka.y + 10, 20,WHITE);
        DrawText("400" , PaneerTikka.x + 500 , PaneerTikka.y + 10 , 20,WHITE);

        DrawRectangleRec(MayoChicken, Fade(RED,0.0f));
        DrawText("Mayo Chicken Sandwich" , MayoChicken.x + 20, MayoChicken.y + 10, 20,WHITE);
        DrawText("300" , MayoChicken.x + 500 ,MayoChicken.y + 10 , 20,WHITE);
        }
    }
    void handleInput(){
        Vector2 mousePoint = GetMousePosition();
        if (order) {
            orderUI.start();
            if (orderUI.stop) {
                order = false;
                orderUI.stop = false; 
            }
            return; 
        }
        if(CheckCollisionPointRec(mousePoint, VegSandwich) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(250);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, PeriPeri) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(350);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, ClubSandwich) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(300);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, PaneerTikka) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(400);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, MayoChicken) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(300);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, Back) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            sandwich = false;
        }
    }
    ~Sandwish() {
        UnloadTexture(texture);
    }
    void Start(){
        handleInput();
        DrawBackgroundGradient();
        DrawSandwich();
    }
};

class Roll {
    private:
    Rectangle ChickenSeekh;
    Rectangle ZingerRoll;
    Rectangle CheeseZingerRoll;
    Rectangle PeriPeri;
    Rectangle VeggieRoll;
    Rectangle Back;
    Texture2D texture;
    public:
    bool roll;
    orderPage orderUI;
    bool order;
    Roll(){
        roll = false;
        order = false;
        Back = {360,450,240,40};
        texture = LoadTexture("background3.jpg");
        ChickenSeekh = {120, 150, 240, 40};
        PeriPeri = {120, 210, 240, 40};
        ZingerRoll = {120, 270, 240, 40};
        CheeseZingerRoll = {120, 330, 240, 40};
        VeggieRoll = {120,390 , 240 ,40};
    }
    void DrawBackgroundGradient() {
        DrawTexture(texture, 0, 0, WHITE);
    }
    void drawRoll(){
        if(order) {
            orderUI.start();
        }
        else if(!order){
        DrawRectangleRec(Back, Fade(RED,0.0f));
        DrawText("Back", Back.x + 20 , Back.y + 10 ,20,WHITE);

        DrawRectangleRec(ChickenSeekh, Fade(RED,0.0f));
        DrawText("Chicken Seekh Roll" , ChickenSeekh.x + 20,ChickenSeekh.y + 10,20,WHITE);
        DrawText("300" , ChickenSeekh.x + 500 , ChickenSeekh.y + 10,20,WHITE);

        DrawRectangleRec(PeriPeri, Fade(RED,0.0f));
        DrawText("Peri Peri Chicken Roll ", PeriPeri.x + 20 , PeriPeri.y + 10, 20, WHITE);
        DrawText("350", PeriPeri.x + 500 ,PeriPeri.y + 10, 20,WHITE);

        DrawRectangleRec(ZingerRoll, Fade(RED,0.0f));
        DrawText("Zinger Roll" , ZingerRoll.x + 20 ,ZingerRoll.y + 10, 20 , WHITE);
        DrawText("400" , ZingerRoll.x + 500 ,ZingerRoll.y + 10 , 20 ,WHITE);

        DrawRectangleRec(CheeseZingerRoll, Fade(RED,0.0f));
        DrawText("Cheese Zinger Roll" , CheeseZingerRoll.x + 20 ,CheeseZingerRoll.y + 10 , 20 ,WHITE);
        DrawText("450", CheeseZingerRoll.x + 500, CheeseZingerRoll.y + 10, 20,WHITE);

        DrawRectangleRec(VeggieRoll , Fade(RED,0.0f));
        DrawText("Veggie Roll" , VeggieRoll.x + 20 ,VeggieRoll.y + 10 ,20 ,WHITE);
        DrawText("250" , VeggieRoll.x + 500 , VeggieRoll.y + 10,20,WHITE);
        }
    }
    void handleInput(){
        Vector2 mousePoint = GetMousePosition();
        if (order) {
            orderUI.start();
            if (orderUI.stop) {
                order = false;
                orderUI.stop = false; 
            }
            return; 
        }
        if(CheckCollisionPointRec(mousePoint, ChickenSeekh) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(300);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, PeriPeri) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(350);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, ZingerRoll) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(400);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, CheeseZingerRoll) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(450);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, VeggieRoll) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(250);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, Back) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            roll = false;
        }
    }
    void start(){
        handleInput();
        DrawBackgroundGradient();
        drawRoll();
    }
};

class IceCream{
    private:
    Rectangle Vanilla_Delight;
    Rectangle Chocolate_Heaven;
    Rectangle Belgian_Chocolate;
    Rectangle Brownie_Sundae;
    Rectangle Pista_Paradise;
    Rectangle Back;
    Texture2D texture;
    public:
    bool iceCream;
    orderPage orderUI;
    bool order;
    IceCream(){
        iceCream = false;
        order = false;
        Back = {360,450,240,40};
        texture = LoadTexture("background3.jpg");
        Vanilla_Delight = {120, 150, 240, 40};
        Chocolate_Heaven = {120, 210, 240, 40};
        Belgian_Chocolate = {120, 270, 240, 40};
        Brownie_Sundae = {120, 330, 240, 40};
        Pista_Paradise = {120,390 , 240 ,40};
    }
    void DrawBackgroundGradient() {
        DrawTexture(texture, 0, 0, WHITE);
    }
    void DrawIceCream(){
        if(order){
            orderUI.start();
        }
        else if(!order) {
        DrawRectangleRec(Back, Fade(RED,0.0f));
        DrawText("Back", Back.x + 20 , Back.y + 10 ,20,WHITE);

        DrawRectangleRec(Vanilla_Delight, Fade(RED,0.0f));
        DrawText("Vanilla Delight", Vanilla_Delight.x + 20, Vanilla_Delight.y + 10, 20,WHITE);
        DrawText("300", Vanilla_Delight.x + 500 ,Vanilla_Delight.y + 10 ,20,WHITE);

        DrawRectangleRec(Chocolate_Heaven , Fade(RED,0.0f));
        DrawText("Chocolate Heaven" , Chocolate_Heaven.x + 20, Chocolate_Heaven.y + 10, 20 ,WHITE);
        DrawText("350" , Chocolate_Heaven.x + 500 , Chocolate_Heaven.y + 10, 20 ,WHITE);

        DrawRectangleRec(Belgian_Chocolate, Fade(RED,0.0f));
        DrawText("Belgian Chocolate" , Belgian_Chocolate.x + 20, Belgian_Chocolate.y + 10 , 20,WHITE);
        DrawText("300", Belgian_Chocolate.x + 500 , Belgian_Chocolate.y + 10 ,20, WHITE);

        DrawRectangleRec(Brownie_Sundae, Fade(RED,0.0f));
        DrawText("Browine Sundae", Brownie_Sundae.x + 20 ,Brownie_Sundae.y + 10, 20, WHITE);
        DrawText("320" , Brownie_Sundae.x + 500, Brownie_Sundae.y + 10, 20,WHITE);

        DrawRectangleRec(Pista_Paradise, Fade(RED,0.0f));
        DrawText("Pista Paradise", Pista_Paradise.x + 20, Pista_Paradise.y + 10, 20, WHITE);
        DrawText("400", Pista_Paradise.x + 500, Pista_Paradise.y + 10, 20, WHITE);
        }
    }
    void handleInput(){
        Vector2 mousePoint = GetMousePosition();
        if (order) {
            orderUI.start();
            if (orderUI.stop) {
                order = false;
                orderUI.stop = false; 
            }
            return; 
        }
        if(CheckCollisionPointRec(mousePoint, Vanilla_Delight) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(300);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, Chocolate_Heaven) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(350);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, Belgian_Chocolate) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(300);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, Brownie_Sundae) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(320);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, Pista_Paradise) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(400);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, Back) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            iceCream = false;
        }
        
    }
    void start(){
        handleInput();
        DrawBackgroundGradient();
        DrawIceCream();
    }
};

class FastFood : public pizza , public burger , public Sandwish , public Roll , public IceCream{
    private:
    User user;
    Rectangle Pizza;
    Rectangle Burger;
    Rectangle Sandwich;
    Rectangle Roll;
    Rectangle IceCream;
    Rectangle box;
    Texture2D texture;
    Rectangle back;
    public:
    bool stop;
    FastFood(){
        stop = false;
        back = {20 ,20 ,240, 30};
        texture = LoadTexture("background3.jpg");
        box = { 250, 150, 300, 330 };
        Pizza = { 280, 200, 240, 40 };
        Burger = { 280, 250, 240, 40 };
        Sandwich = { 280, 300, 240, 40 };
        Roll = { 280, 350, 240, 40 };
        IceCream = { 280, 400, 240, 40 };
    }
    void DrawBackgroundGradient(int w, int h) {
        DrawTexture(texture, 0, 0, WHITE);
    }
    void DrawFastFoodScreen(){
        if(pizza::Pizza){
            pizza::start();
        }
        else if(burger::Burger){
            burger::start();
        }
        else if(Sandwish::sandwich){
            Sandwish::Start();
        }
        else if(Roll::roll){
            Roll::start();
        }
        else if(IceCream::iceCream){
            IceCream::start();
        }
        else if (pizza::Pizza == false && burger::Burger == false && Sandwish::sandwich == false && Roll::roll == false && IceCream::iceCream == false){
        DrawRectangleRec(Pizza, (Color){255, 80, 80, 255});
        DrawRectangleLinesEx(Pizza, 2, DARKGRAY);
        DrawText("Pizza", Pizza.x + 90, Pizza.y + 10, 20, WHITE);

        DrawRectangleRec(Burger, (Color){255, 165, 0, 255});
        DrawRectangleLinesEx(Burger, 2, DARKGRAY);
        DrawText("Burger", Burger.x + 85, Burger.y + 10, 20, WHITE);

        DrawRectangleRec(Sandwich, (Color){0, 150, 255, 255});
        DrawRectangleLinesEx(Sandwich, 2, DARKGRAY);
        DrawText("Sandwich", Sandwich.x + 70, Sandwich.y + 10, 20, WHITE);

        DrawRectangleRec(Roll, (Color){100, 255, 100, 255});
        DrawRectangleLinesEx(Roll, 2, DARKGRAY);
        DrawText("Roll", Roll.x + 105, Roll.y + 10, 20, WHITE);

        DrawRectangleRec(IceCream, (Color){200, 100, 255, 255});
        DrawRectangleLinesEx(IceCream, 2, DARKGRAY);
        DrawText("Ice Cream", IceCream.x + 70, IceCream.y + 10, 20, WHITE);

        DrawRectangleRec(back, Fade(RED,0.0f));
        DrawText("<-" , back.x , back.y , 30, WHITE);
        }
    }
    void HandleInput(){
        Vector2 mousePoint = GetMousePosition();

        if(CheckCollisionPointRec(mousePoint , Burger) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && burger::Burger == false && pizza::Pizza == false && Sandwish::sandwich == false && Roll::roll == false && IceCream::iceCream == false){
            burger::Burger = true ;
            cout << " Desi !!!!!" << endl;
        }
        if(CheckCollisionPointRec(mousePoint , Pizza) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && burger::Burger == false && pizza::Pizza == false && Sandwish::sandwich == false && Roll::roll == false && IceCream::iceCream == false){
            pizza::Pizza = true;
        }
        if(CheckCollisionPointRec(mousePoint , Sandwich) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && burger::Burger == false && pizza::Pizza == false && Sandwish::sandwich == false && Roll::roll == false && IceCream::iceCream == false){
            Sandwish::sandwich = true;
        }
        if(CheckCollisionPointRec(mousePoint , Roll) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && burger::Burger == false && pizza::Pizza == false && Sandwish::sandwich == false && Roll::roll == false && IceCream::iceCream == false){
            Roll::roll= true;
        }
        if(CheckCollisionPointRec(mousePoint , IceCream) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && burger::Burger == false && pizza::Pizza == false && Sandwish::sandwich == false && Roll::roll == false && IceCream::iceCream == false){
            IceCream::iceCream = true;
        }
        if(CheckCollisionPointRec(mousePoint , back) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && burger::Burger == false && pizza::Pizza == false && Sandwish::sandwich == false && Roll::roll == false && IceCream::iceCream == false){
            stop = true;
        }
    }
    void getUser(User user){
        this->user = user;
    }
    void Start(){
        DrawBackgroundGradient(800, 600);
        HandleInput();
        DrawFastFoodScreen();
        if(pizza::order){
            pizza::orderUI.getUser(user);
        }
        else if(burger::order){
            burger::orderUI.getUser(user);
        }
        else if(Sandwish::order){
            Sandwish::orderUI.getUser(user);
        }
        else if(Roll::order){
            Roll::orderUI.getUser(user);
        }
        else if(IceCream::order){
            IceCream::orderUI.getUser(user);
        }
    }
};

class Karahi{
    private:
    Rectangle ChickenKarahi;
    Rectangle MuttonKarahi;
    Rectangle ChickenWhite;
    Rectangle MuttonShinwari;
    Rectangle AchariChicken;
    Rectangle Back;
    Texture2D texture;
    Rectangle half;
    Rectangle full;
    public:
    orderPage orderUI;
    bool order;
    bool chickenkarahi;
    bool muttonkarahi;
    bool chickenwhite;
    bool muttonshinwari;
    bool acharichicken;
    bool karahi;
    bool quantity;
    Karahi(){
        quantity = false;
        chickenkarahi = false;
        muttonkarahi = false;
        chickenkarahi = false;
        muttonshinwari = false;
        acharichicken = false;
        karahi = false;
        order = false;
        Back = {360,450,240,40};
        texture = LoadTexture("background3.jpg");
        ChickenKarahi = {120, 150, 240, 40};
        MuttonKarahi = {120, 210, 240, 40};
        ChickenWhite = {120, 270, 240, 40};
        MuttonShinwari = {120, 330, 240, 40};
        AchariChicken = {120,390 , 240 ,40};
        half = { 280, 230, 240, 40 };
        full = { 280, 290, 240, 40 };
    }
    void DrawBackgroundGradient() {
        DrawTexture(texture, 0, 0, WHITE);
    }
    void DrawKarahi(){
        if(quantity == true  && order == false){
            DrawRectangleRec(half, (Color){255, 140, 0, 255});
            DrawRectangleLinesEx(half, 1, DARKGRAY);
            DrawText("HALF", half.x + 90, half.y + 10, 20, WHITE);
    
            DrawRectangleRec(full, (Color){200, 30, 60, 255});
            DrawRectangleLinesEx(full, 1, DARKGRAY);
            DrawText("FULL", full.x + 85, full.y + 10, 20, WHITE);
        }
        else if(order == true){
            orderUI.start();
        }
        else if(quantity == false && order == false){
        DrawRectangleRec(Back, Fade(RED,0.0f));
        DrawText("Back", Back.x + 20 , Back.y + 10 ,20,WHITE);

        DrawRectangleRec(ChickenKarahi , Fade(RED,0.0f));
        DrawText("Chicken Peshawari Karahi" , ChickenKarahi.x + 20 , ChickenKarahi.y + 10, 20, WHITE);
        DrawText("Full", ChickenKarahi.x + 500, ChickenKarahi.y - 20, 20, WHITE);
        DrawText("2800" , ChickenKarahi.x + 500 , ChickenKarahi.y + 10, 20,WHITE );
        DrawText("Half", ChickenKarahi.x + 450, ChickenKarahi.y - 20, 20, WHITE);
        DrawText("1900", ChickenKarahi.x + 450, ChickenKarahi.y + 10, 20, WHITE);

        DrawRectangleRec(MuttonKarahi , Fade(RED,0.0f));
        DrawText("Mutton Peshawari Karahi" , MuttonKarahi.x + 20 , MuttonKarahi.y + 10, 20, WHITE);
        DrawText("3800" , MuttonKarahi.x + 500 , MuttonKarahi.y + 10, 20,WHITE );
        DrawText("3000" , MuttonKarahi.x  + 450 , MuttonKarahi.y + 10 , 20 , WHITE);

        DrawRectangleRec(ChickenWhite , Fade(RED,0.0f));
        DrawText("Chicken White Karahi" , ChickenWhite.x + 20 , ChickenWhite.y + 10, 20, WHITE);
        DrawText("2600" , ChickenWhite.x + 500 , ChickenWhite.y + 10, 20,WHITE );
        DrawText("1900" , ChickenWhite.x + 450 , ChickenWhite.y + 10, 20,WHITE );

        DrawRectangleRec(MuttonShinwari , Fade(RED,0.0f));
        DrawText("Mutton Shinwar Karahi" , MuttonShinwari.x + 20 , MuttonShinwari.y + 10, 20, WHITE);
        DrawText("3600" , MuttonShinwari.x + 500 , MuttonShinwari.y + 10, 20,WHITE );
        DrawText("2800" , MuttonShinwari.x + 450 , MuttonShinwari.y + 10, 20,WHITE );

        DrawRectangleRec(AchariChicken , Fade(RED,0.0f));
        DrawText("Chicken Achari Karahi" , AchariChicken.x + 20 , AchariChicken.y + 10, 20, WHITE);
        DrawText("2700" , AchariChicken.x + 500 , AchariChicken.y + 10, 20,WHITE );
        DrawText("1800" , AchariChicken.x  + 450 , AchariChicken.y + 10 ,20 ,WHITE);
        }
    }
    void handleInput(){
        Vector2 mousePoint = GetMousePosition();
        if(!quantity){
        if(CheckCollisionPointRec(mousePoint, Back) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            karahi = false;
        }
        if(CheckCollisionPointRec(mousePoint, ChickenKarahi) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            chickenkarahi = true;
            quantity = true;
        }
        if(CheckCollisionPointRec(mousePoint, MuttonKarahi) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            muttonkarahi = true;
            quantity = true;
        }
        if(CheckCollisionPointRec(mousePoint, ChickenWhite) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            chickenwhite = true;
            quantity = true;
        }
        if(CheckCollisionPointRec(mousePoint, MuttonShinwari) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            muttonshinwari = true;
            quantity = true;
        }
        if(CheckCollisionPointRec(mousePoint, AchariChicken) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            acharichicken = true;
            quantity = true;
        }
        }
        else if(quantity){
            if (order) {
                orderUI.start();
                if (orderUI.stop) {
                    order = false;
                    orderUI.stop = false; 
                    quantity = false;
                }
                return; 
            }
            if(CheckCollisionPointRec(mousePoint, half) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                order = true;
                if(chickenkarahi)orderUI.setprice(1900);
                else if(chickenwhite)orderUI.setprice(1900);
                else if(muttonkarahi)orderUI.setprice(3000);
                else if(muttonshinwari)orderUI.setprice(2800);
                else if(acharichicken)orderUI.setprice(1800);
            }
            if(CheckCollisionPointRec(mousePoint, full) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                order = true;
                if(chickenkarahi)orderUI.setprice(2800);
                else if(chickenwhite)orderUI.setprice(2600);
                else if(muttonkarahi)orderUI.setprice(3000);
                else if(muttonshinwari)orderUI.setprice(3800);
                else if(acharichicken)orderUI.setprice(2700);
            }
            if(orderUI.stop){
                order = false;
            }
        }
    }
    void Start(){
        DrawBackgroundGradient();
        handleInput();
        DrawKarahi();
    }
};

class Biryani{
    private:
    Rectangle ChickenBiryani;
    Rectangle BeefBiryani;
    Rectangle ChickenPulao;
    Rectangle special;
    Rectangle Back;
    Texture2D texture;
    public:
    orderPage orderUI;
    bool order;
    bool biryani;
    Biryani(){
        biryani = false;
        order = false;
        texture = LoadTexture("background3.jpg");
        Back = {360,440,240,40};
        ChickenBiryani = {120, 160, 240, 40};
        BeefBiryani = {120, 220, 240, 40};
        ChickenPulao = {120, 280, 240, 40};
        special = {120, 340, 240, 40};
    }
    void DrawBackgroundGradient() {
        DrawTexture(texture, 0, 0, WHITE);
    }
    void DrawBiryani(){
        if(order){
            orderUI.start();
        }
        else if(!order){
        DrawRectangleRec(Back, Fade(RED,0.0f));
        DrawText("Back", Back.x + 20 , Back.y + 10 ,20,WHITE);

        DrawRectangleRec(ChickenBiryani , Fade(RED,0.0f));
        DrawText("Chicken Biryani", ChickenBiryani.x + 20 , ChickenBiryani.y + 10 ,20,WHITE );
        DrawText("380", ChickenBiryani.x + 500 , ChickenBiryani.y + 10 ,20,WHITE );

        DrawRectangleRec(BeefBiryani , Fade(RED,0.0f));
        DrawText("Beef Biryani" , BeefBiryani.x + 20 , BeefBiryani.y + 10 , 20 ,WHITE );
        DrawText("450" , BeefBiryani.x + 500 , BeefBiryani.y + 10 , 20 ,WHITE );

        DrawRectangleRec(ChickenPulao , Fade(RED,0.0f));
        DrawText("Chicken Pulao" , ChickenPulao.x + 20 ,ChickenPulao.y + 20, 20,WHITE);
        DrawText("300" , ChickenPulao.x + 500 ,ChickenPulao.y + 20, 20,WHITE);

        DrawRectangleRec(special , Fade(RED,0.0f));
        DrawText("Special Biryani" , special.x + 20 ,special.y + 10 ,20,WHITE);
        DrawText("420" , special.x + 500 ,special.y + 10 , 20, WHITE);
        }
    }
    void handleInput(){
        Vector2 mousePoint = GetMousePosition();
        if (order) {
            orderUI.start();
            if (orderUI.stop) {
                order = false;
                orderUI.stop = false; 
            }
            return; 
        }
        if(CheckCollisionPointRec(mousePoint, ChickenBiryani) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(380);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, BeefBiryani ) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(450);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, ChickenPulao) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(300);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, special) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(420);
            order = true;
        }if(CheckCollisionPointRec(mousePoint, Back) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            biryani = false;
        }
    }
    void Start(){
        DrawBackgroundGradient();
        DrawBiryani();
        handleInput();
    }
};

class bbq{
    private:
    Rectangle ChickenTikka;
    Rectangle BehariChicken;
    Rectangle GolaChicken;
    Rectangle AfghaniBoti;
    Rectangle FishTikka;
    Rectangle Back;
    Texture2D texture;
    public:
    orderPage orderUI;
    bool order;
    bool BBQ;
    bbq(){
        BBQ = false;
        order = false;
        Back = {360,450,240,40};
        texture = LoadTexture("background3.jpg");
        ChickenTikka = {120, 150, 240, 40};
        BehariChicken = {120, 210, 240, 40};
        GolaChicken = {120, 270, 240, 40};
        AfghaniBoti = {120, 330, 240, 40};
        FishTikka = {120,390 , 240 ,40};
    }
    void DrawBackgroundGradient() {
        DrawTexture(texture, 0, 0, WHITE);
    }
    void drawBBQ(){
        DrawRectangleRec(Back, Fade(RED,0.0f));
        DrawText("Back", Back.x + 20 , Back.y + 10 ,20,WHITE);

        DrawRectangleRec(ChickenTikka, Fade(RED,0.0f));
        DrawText("Chicken Tikka" , ChickenTikka.x + 20 , ChickenTikka.y + 10 ,20, WHITE);
        DrawText("350" , ChickenTikka.x + 500 , ChickenTikka.y + 10 ,20, WHITE);

        DrawRectangleRec(BehariChicken , Fade(RED,0.0f));
        DrawText("Behari Chiken" , BehariChicken.x + 20 , BehariChicken.y + 10, 20, WHITE);
        DrawText("400" , BehariChicken.x + 500 , BehariChicken.y + 10, 20, WHITE);

        DrawRectangleRec(GolaChicken, Fade(RED,0.0f));
        DrawText("Gola Kahab" , GolaChicken.x + 20 ,GolaChicken.y + 10 ,20,WHITE);
        DrawText("500" , GolaChicken.x + 500 ,GolaChicken.y + 10 ,20,WHITE);

        DrawRectangleRec(AfghaniBoti, Fade(RED,0.0f));
        DrawText("Chicken Afghani Boti" , AfghaniBoti.x + 20 ,AfghaniBoti.y + 10 ,20, WHITE);
        DrawText("450" , AfghaniBoti.x + 500 ,AfghaniBoti.y + 10 ,20, WHITE);

        DrawRectangleRec(FishTikka , Fade(RED,0.0f));
        DrawText("Fish Tikka" , FishTikka.x + 20 ,FishTikka.y + 10 , 20, WHITE);
        DrawText("600", FishTikka.x + 500, FishTikka.y + 10 ,20, WHITE);
        
    }
    void handleInput(){
        Vector2 mousePoint = GetMousePosition();
        if (order) {
            orderUI.start();
            if (orderUI.stop) {
                order = false;
                orderUI.stop = false; 
            }
            return; 
        }
    
        if(CheckCollisionPointRec(mousePoint, ChickenTikka) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(350);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, BehariChicken) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(400);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, GolaChicken) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(500);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, AfghaniBoti) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(450);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, FishTikka) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(600);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, Back) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            BBQ = false;
        }
    }
    
    void Start(){
        DrawBackgroundGradient();
        drawBBQ();
        handleInput();
    }
};

class Handi{
    private:
    Rectangle ChickenBoneless;
    Rectangle ChickenMakhni;
    Rectangle ChickenGreen;
    Rectangle PaneerReshmi;
    Rectangle MuttonWhite;
    Rectangle Back;
    Texture2D texture;
    public:
    bool handi;
    orderPage orderUI;
    bool order;
    Handi(){
        handi = false;
        order = false;
        Back = {360,450,240,40};
        texture = LoadTexture("background3.jpg");
        ChickenBoneless = {120, 150, 240, 40};
        ChickenMakhni = {120, 210, 240, 40};
        ChickenGreen = {120, 270, 240, 40};
        PaneerReshmi = {120, 330, 240, 40};
        MuttonWhite = {120,390 , 240 ,40};
    }
    void DrawBackgroundGradient() {
        DrawTexture(texture, 0, 0, WHITE);
    }
    void DrawHandi(){
        DrawRectangleRec(Back, Fade(RED,0.0f));
        DrawText("Back", Back.x + 20 , Back.y + 10 ,20,WHITE);

        DrawRectangleRec(ChickenBoneless, Fade(RED,0.0f));
        DrawText("Chicken Boneless Handi" , ChickenBoneless.x + 20 , ChickenBoneless.y + 10 ,20, WHITE);
        DrawText("2800" , ChickenBoneless.x + 500 , ChickenBoneless.y + 10 ,20, WHITE);

        DrawRectangleRec(ChickenMakhni , Fade(RED,0.0f));
        DrawText("Chicken Makhni Handi" , ChickenMakhni.x + 20 , ChickenMakhni.y + 10, 20, WHITE);
        DrawText("2600" , ChickenMakhni.x + 500 , ChickenMakhni.y + 10, 20, WHITE);

        DrawRectangleRec(ChickenGreen, Fade(RED,0.0f));
        DrawText("Chicken Green Handi" , ChickenGreen.x + 20 ,ChickenGreen.y + 10 ,20,WHITE);
        DrawText("2500" , ChickenGreen.x + 500 ,ChickenGreen.y + 10 ,20,WHITE);

        DrawRectangleRec(PaneerReshmi, Fade(RED,0.0f));
        DrawText("Paneer Reshmi Handi" , PaneerReshmi.x + 20 ,PaneerReshmi.y + 10 ,20, WHITE);
        DrawText("1800" , PaneerReshmi.x + 500 ,PaneerReshmi.y + 10 ,20, WHITE);

        DrawRectangleRec(MuttonWhite , Fade(RED,0.0f));
        DrawText("Mutton White Handi" , MuttonWhite.x + 20 ,MuttonWhite.y + 10 , 20, WHITE);
        DrawText("3600", MuttonWhite.x + 500, MuttonWhite.y + 10 ,20, WHITE);
    }
    void handleInput(){
        Vector2 mousePoint = GetMousePosition();
        if (order) {
            orderUI.start();
            if (orderUI.stop) {
                order = false;
                orderUI.stop = false; 
            }
            return; 
        }
        if(CheckCollisionPointRec(mousePoint, ChickenBoneless) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(2800);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, ChickenMakhni) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(2600);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, ChickenGreen) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(2500);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, PaneerReshmi) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(1800);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, MuttonWhite) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            orderUI.setprice(3600);
            order = true;
        }
        if(CheckCollisionPointRec(mousePoint, Back) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            handi = false;
        }
    }
    void Start(){
        DrawBackgroundGradient();
        DrawHandi();
        handleInput();
    }
};

class DesiMenu : public Handi , public IceCream , public Karahi , public bbq , public Biryani{
    private:
    User user;
    Rectangle Karahi;
    Rectangle Biryani_Rice;
    Rectangle BBQ_Grilled;
    Rectangle Handi_Specials;
    Rectangle IceCream;
    Rectangle back;
    Texture2D texture;
    public:
    bool stop;
    DesiMenu(){
        stop = false;
        back = {20 ,20 ,240, 30};
        texture = LoadTexture("background3.jpg");
        Karahi = {280, 200, 240, 40};
        Biryani_Rice = {280, 250, 240, 40};
        BBQ_Grilled = {280, 300, 240, 40};
        Handi_Specials = {280, 350, 240, 40};
        IceCream = {280,400 , 240 ,40};
    }
    void DrawBackgroundGradient() {
        DrawTexture(texture, 0, 0, WHITE);
    }
    void DrawDesi(){
        if(iceCream == true){
            IceCream::start();
        }
        else if(biryani == true){
            Biryani::Start();
        }
        else if(BBQ == true){
            bbq::Start();
        }
        else if(karahi == true){
            Karahi::Start();
        }
        else if(handi == true){
            Handi::Start();
        }
        else if (iceCream == false && handi== false && karahi == false && BBQ == false && biryani == false){
        DrawRectangleRec(Karahi, (Color){255, 80, 80, 255});
        DrawRectangleLinesEx(Karahi, 2, DARKGRAY);
        DrawText("Karahi", Karahi.x + 80, Karahi.y + 10, 20, WHITE);

        DrawRectangleRec(Biryani_Rice, (Color){255, 165, 0, 255});
        DrawRectangleLinesEx(Biryani_Rice, 2, DARKGRAY);
        DrawText("Biryani Rice", Biryani_Rice.x + 60, Biryani_Rice.y + 10, 20, WHITE);

        DrawRectangleRec(BBQ_Grilled, (Color){0, 150, 255, 255});
        DrawRectangleLinesEx(BBQ_Grilled, 2, DARKGRAY);
        DrawText("BBQ Grilled", BBQ_Grilled.x + 60, BBQ_Grilled.y + 10, 20, WHITE);

        DrawRectangleRec(Handi_Specials, (Color){100, 255, 100, 255});
        DrawRectangleLinesEx(Handi_Specials, 2, DARKGRAY);
        DrawText("Handi Special", Handi_Specials.x + 60, Handi_Specials.y + 10, 20, WHITE);

        DrawRectangleRec(IceCream, (Color){200, 100, 255, 255});
        DrawRectangleLinesEx(IceCream, 2, DARKGRAY);
        DrawText("Ice Cream", IceCream.x + 60, IceCream.y + 10, 20, WHITE);

        DrawRectangleRec(back, Fade(RED,0.0f));
        DrawText("<-" , back.x , back.y , 30, WHITE);
        }
    }
    
    void HadleInput(){
        Vector2 mousePoint = GetMousePosition();
        if(CheckCollisionPointRec(mousePoint , Karahi) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && karahi == false && iceCream == false && biryani == false && BBQ == false && handi == false){
            karahi = true;
        }
        if(CheckCollisionPointRec(mousePoint , Biryani_Rice) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && karahi == false && iceCream == false && biryani == false && BBQ == false && handi == false){
            biryani = true;
        }
        if(CheckCollisionPointRec(mousePoint , BBQ_Grilled) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && karahi == false && iceCream == false && biryani == false && BBQ == false && handi == false){
            BBQ = true;
        }
        if(CheckCollisionPointRec(mousePoint , Handi_Specials) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && karahi == false && iceCream == false && biryani == false && BBQ == false && handi == false){
            handi = true;
        }
        if(CheckCollisionPointRec(mousePoint , IceCream) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && karahi == false && iceCream == false && biryani == false && BBQ == false && handi == false){
            iceCream = true;
        }
        if(CheckCollisionPointRec(mousePoint , back) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && karahi == false && iceCream == false && biryani == false && BBQ == false && handi == false){
            stop = true;
        }
    }
    void getUser(User user){
        this-> user = user;
    }
    void start(){
        DrawBackgroundGradient();
        DrawDesi();
        HadleInput();
        if(Karahi::order){
            Karahi::orderUI.getUser(user);
        }
        else if(Biryani::order){
            Biryani::orderUI.getUser(user);
        }
        else if(bbq::order){
            bbq::orderUI.getUser(user);
        }
        else if(Handi::order){
            Handi::orderUI.getUser(user);
        }
        else if(IceCream::order){
            IceCream::orderUI.getUser(user);
        }
    }
};


class Menu{
    private:
    Rectangle desiFood;
    Rectangle fastFood;
    Rectangle menuBox;
    Texture2D texture ;
    Rectangle back;
    Rectangle Historybutton;
    public:
    History h1;
    bool history = false;
    bool stop;
    bool fast = false;
    bool desi = false;
    Menu(){
        stop = false;
        Historybutton = {600,20,240,30};
        back = {20 ,20 ,240, 30};
        texture = LoadTexture("background3.jpg");
        desiFood = { 280, 250, 240, 40 };
        fastFood = { 280, 310, 240, 40 };
        menuBox = {250,150,300,250};
    }
    void HandleInput(){
        Vector2 mousePoint = GetMousePosition();

        if(CheckCollisionPointRec(mousePoint , desiFood) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            desi = true;
        }
        if(CheckCollisionPointRec(mousePoint , fastFood) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            fast = true;
        }
        if(CheckCollisionPointRec(mousePoint , back) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            stop = true;
        }
        if(CheckCollisionPointRec(mousePoint , Historybutton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            history = true;
        }
        if(h1.getStop()){
            history = false;
        }
    }
    void DrawBackgroundGradient(int w, int h) {
        DrawTexture(texture, 0, 0, WHITE);
    }
    void drawMenu(){
        if(history == true){
            h1.Start();
        }
        else{
        DrawRectangleRec(menuBox ,RAYWHITE);
        DrawRectangleLinesEx(menuBox, 2, DARKGRAY); 
        DrawText("Choose Option Of Food",290,180,20,BLACK);

        DrawRectangleRec(desiFood, (Color){255, 140, 0, 255});
        DrawRectangleLinesEx(desiFood, 1, DARKGRAY);
        DrawText("Desi Food", desiFood.x + 65, desiFood.y + 10, 20, WHITE);

        DrawRectangleRec(fastFood, (Color){200, 30, 60, 255});
        DrawRectangleLinesEx(fastFood, 1, DARKGRAY);
        DrawText("Fast Food", fastFood.x + 60, fastFood.y + 10, 20, WHITE);

        DrawRectangleRec(back, Fade(RED,0.0f));
        DrawText("<-" , back.x , back.y , 30, WHITE);

        DrawRectangleRec(Historybutton,Fade(RED,0.0f));
        DrawText("History",Historybutton.x + 50, Historybutton.y + 10, 20,WHITE);
        }
    }
    void start(){
        DrawBackgroundGradient(800,600);
        HandleInput();
        drawMenu();
    }
};


int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Auth Form - OOP Raylib");

    SetTraceLogCallback(nullptr); 

    SetTargetFPS(60);
    History h1;
    
    Roll roll;
    LoginForm auth;
    Menu menu;
    FastFood Fast;
    burger Burger;
    pizza Pizza;
    Sandwish sandwich;
    DesiMenu desiMenu;
    bbq BBQ;
    Karahi karahi;
    Handi handi;
    Biryani biryani;
    IceCream icecream;
    orderPage Order;
    
    

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // h1.DrawBackgroundGradient();
        // h1.draw();
        
        if (!auth.menu) {
            auth.start(screenWidth, screenHeight);
        } else {
            if (!menu.fast && !menu.desi) {
                menu.start();
                menu.h1.getUser(auth.getUser());
                if(menu.stop){
                    CloseWindow();
                    return 0;
                }
            } else if (menu.fast){
                Fast.Start();
                Fast.getUser(auth.getUser());
                if(Fast.stop){
                    menu.fast = false;
                }
            }
            else if(menu.desi == true){
                desiMenu.start();
                desiMenu.getUser(auth.getUser());
                if(desiMenu.stop){
                    menu.desi = false;
                }
            }
            
        }
        

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
