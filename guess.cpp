#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cctype>
#include <fstream>
using namespace std;

//我来猜
void guess(int &outTries, int &outTime){
    int choice = 0;
    int MAX_TRIES = 0;
    int MIN_NUMBER = 1;
    int MAX_NUMBER = 0;

    while(1){
        cout << "Choose difficulty: " << endl;
        cout << "1.Easy (1-50, 8 tries)" << endl;
        cout << "2.Normal (1-100, 8 tries)" << endl;
        cout << "3.Hard (1-200, 7 tries)" << endl;
        cout << "4.Custom range" << endl;

        cin >> choice;
        if(cin.fail() || cin.get() != '\n'){           //检查缓冲区是否含有残留字符
            cin.clear();
            cin.ignore(10000,'\n');
            cout << "Invalid input.Please enter a number.(1/2/3/4)" << endl;
        }else if(choice >= 1 && choice <= 4){
            break;
        }else{
            cout << "Please enter 1,2,3 or 4." << endl;
        }
    }

    if(choice == 1){
        MAX_TRIES = 8;
        MAX_NUMBER = 50;
    }else if(choice == 2){
        MAX_TRIES = 8;
        MAX_NUMBER = 100;
    }else if(choice == 3){
        MAX_TRIES = 7;
        MAX_NUMBER = 200;
    }else if(choice == 4){
        while(1){

            while(true){
                cout << "Please enter the tries: " << endl;
                cin >> MAX_TRIES;
                if(cin.fail() || cin.get() != '\n'){
                    cin.clear();
                    cin.ignore(10000,'\n');
                    cout << "Invalid input. Please enter an integer." << endl;
                }else if(MAX_TRIES < 0){
                    cout << "Invalid input! Try again." << endl;
                }else{
                    break;
                }
            }
        
            while(true){
                cout << "Please enter the minimum number: " << endl;
                cin >> MIN_NUMBER;
                if(cin.fail() || cin.get() != '\n'){
                    cin.clear();
                    cin.ignore(10000,'\n');
                    cout << "Invalid input. Please enter an integer." << endl;
                }else{
                    break;
                }
            }
         
            while(true){
                cout << "Please enter the maximum number: " << endl;
                cin >> MAX_NUMBER;
                if(cin.fail() || cin.get() != '\n'){
                    cin.clear();
                    cin.ignore(10000,'\n');
                    cout << "Invalid input. Please enter an integer." << endl;
                }else{
                    break;
                }
            }

            if(MIN_NUMBER > MAX_NUMBER) {
                cout << "Invalid input! Try again." << endl;
            }else{
                break;
            }
            
        }
        
    }

    int secret = rand() % (MAX_NUMBER - MIN_NUMBER + 1) + MIN_NUMBER;     //rand()%个数+起始值
    int guess;
    int count = 0;
    time_t startTime =  time(0);

    cout << "I have chosen a number between " << MIN_NUMBER << " and " << MAX_NUMBER << ". Try to guess it!" << endl;

    while(1){
        cin >> guess;
        count ++;
        if(cin.fail()){                //发现读取失败
            cin.clear();               //清除cin错误状态
            cin.ignore(10000,'\n');     //清空缓存区（忽略到换行），不然每次循环都会读取到缓存区不是数字的错误数据而无法输入新数据
            cout << "Invalid input.Please enter a number.You have " << (MAX_TRIES - count) << " tries left." << endl;
            continue;                   //跳过后面的判断，重新开始循环
        }
        
        if(guess == secret){
            cout << "Great! You made it! The right number is " << secret << " ." << endl;
            cout << "You have tried " << count << " times." << endl;
            break;
        }else if(guess > secret){
            cout << "Too high! You have " << (MAX_TRIES - count) << " tries left." << endl;
        }else{
            cout << "Too low! You have " << (MAX_TRIES - count) << " tries left." << endl;
        }

        if(count >= MAX_TRIES){
            cout << "Sorry, you've used all " << MAX_TRIES << " tries. " << endl;
            cout << "The correct number is " << secret << " ." << endl;
            count = 999;
            break;
        }
    }
    
    time_t endTime = time(0);
    int seconds = endTime - startTime;
    cout << "This round took you about " << seconds << " seconds." << endl;
    
    outTries = count;
    outTime = seconds;
}

void Judge(int currentTries , int &bestScore , int currentTime , int &bestTime){
    bool isNewBest = false;

    if(currentTries == 999){
        cout << "I'm sorry.You have failed." << endl;
    }else if(currentTries < bestScore){
        isNewBest = true;
    }else if(currentTries == bestScore && currentTime < bestTime) {
        isNewBest = true;
    }
    
    if(isNewBest){
        bestScore = currentTries;
        bestTime = currentTime;
        cout << "New best score! " << bestScore << " tries in " << bestTime << " seconds." << endl;
    }else if(!isNewBest && currentTries != 999){
        cout << "Current best: " << bestScore << " tries in " << bestTime << " seconds." << endl;
    }

    
}

//电脑来猜
void computerguess(int minnumber , int maxnumber){
    int low = minnumber;
    int high = maxnumber;
    int attempts = 0;
    char feedback;

    cout << "Think of a number between " << minnumber << " and " << maxnumber << endl;
    cout << "I will try to guess it. Please respond with: " << endl;
    cout <<"H = too high, L = too low, C = correct" << endl;
    
    int guess;
    time_t startTime =  time(0);
    while(low <= high){
        guess = (low + high) / 2;

        cout << "My guess is " << guess << "." << endl;

        while(1){
            cout << "Please enter your feedback(H/L/C): " << endl;
            cin >> feedback;
            feedback = toupper(feedback);        //转成大写，方便判断
            if(feedback != 'H' && feedback != 'L' && feedback != 'C'){
                cout << "Invalid input.Try again!" << endl;
            }else{
                break;
            }
        }

        attempts ++;
        
        if(feedback == 'C'){
            cout << "I got it in " << attempts << " attempts!" << endl;
            break;
        }else if(feedback == 'H'){
            high = guess-1;
        }else if(feedback == 'L'){
            low = guess+1;
        }

        if(low > high){
            cout << "Yout feedback is inconsistent!" << endl;
        }

    }
    
    time_t endTime = time(0);
    int seconds = endTime - startTime;
    cout << "The round have took about " << seconds << " seconds." << endl;
}

int main(){
    srand(time(0));       //设置随机数的种子

//两个玩法，我猜或者电脑猜
    cout << "Please choose: " << endl;
    cout << "1. I guess" << endl;
    cout << "2. The computer guess" << endl;

    int choice1;
    while(1){
        cin >> choice1;
        if(cin.fail() || cin.get() != '\n'){
            cin.clear();
            cin.ignore(10000,'\n');
            cout << "Invalid input,please enter a integer.(1/2)" << endl;
        }else  if(choice1 == 1 || choice1 == 2){
            break;
        }else{
            cout << "Please enter 1 or 2." << endl;
        } 
    }

    if(choice1 == 1){
        int bestScore = 999;
        int bestTime = 9999;
        int currentTries, currentTime;
    
        ifstream inFile("best_score.txt");
        if(inFile.is_open()){
            inFile >> bestScore >> bestTime;
            inFile.close();
        }

        guess(currentTries, currentTime);
        Judge (currentTries , bestScore , currentTime , bestTime); 

        while(1){ 
            cout << "Do you want to play again? Write your answer down.(yes/no) " << endl;
            string answer;
            cin >> answer;
            for(char &c : answer){
                c = tolower(c);
            }                               //不区分大小写

            if(answer == "yes"){
                guess(currentTries, currentTime);
                Judge(currentTries , bestScore , currentTime , bestTime);
            }else if (answer == "no"){
                ofstream outFile("best_score.txt");
                if(outFile.is_open()){
                    outFile << bestScore << " " << bestTime;
                    outFile.close();
                }
                break;
            }else{
                cout << "Invalid input. Please enter yes or no." << endl;
            }  
        }
    }else{
        int high,low;
        while(1){
            while(1){
                cout << "Please enter the minimum number: " << endl;
                cin >> low;
                if(cin.fail() || cin.get() != '\n'){
                    cin.clear();
                    cin.ignore(10000,'\n');
                    cout << "Invalid input,please enter a integer." << endl;
                }else{
                    break;
                }
            }

            while(1){
                cout << "Please enter maximum number: " << endl;
                cin >> high;
                if(cin.fail() || cin.get() != '\n'){
                    cin.clear();
                    cin.ignore(10000,'\n');
                    cout << "Invalid input,please enter a integer.(1/2)" << endl;
                }else{
                    break;
                }
            }

            if(high < low){
                cout << "Invalid input! Try again. " << endl;
            }else{
                break;
            }
        }
        
        computerguess(low , high);
        
    }
  
    system ("pause");         //只有windows系统能用，建议删除。
    return 0;
}