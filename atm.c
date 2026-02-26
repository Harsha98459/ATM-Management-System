#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

float amount = 0.00;

/* --- LOGIC: DATE & TIME --- */
void getDateTime(char *buffer, size_t buffer_size) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    if (tm_info != NULL) {
        strftime(buffer, buffer_size, "%Y-%m-%d %H:%M:%S", tm_info);
    } else {
        snprintf(buffer, buffer_size, "N/A");
    }
}

/* --- LOGIC: FILE OPERATIONS --- */
void loadBalance() {
    FILE *fbal = fopen("balance.txt", "r");
    if (fbal == NULL) {
        amount = 5000.00; 
        fbal = fopen("balance.txt", "w");
        if (fbal != NULL) {
            fprintf(fbal, "%.2f", amount);
            fclose(fbal);
        }
    } else {
        if (fscanf(fbal, "%f", &amount) != 1) {
            amount = 5000.00;
        }
        fclose(fbal);
    }
}

void saveBalance() {
    FILE *fbal = fopen("balance.txt", "w");
    if (fbal != NULL) {
        fprintf(fbal, "%.2f", amount);
        fclose(fbal);
    }
}

void logTransaction(const char* type, float amt) {
    char dt[50];
    getDateTime(dt, sizeof(dt));
    FILE *fhist = fopen("history.txt", "a");
    if (fhist != NULL) {
        fprintf(fhist, "[%s] %s: %.2f | New Balance: %.2f\n", dt, type, amt, amount);
        fclose(fhist);
    }
}

/* --- TRILINGUAL CONTENT MAP --- */
const char* ui[3][20] = {
    // English [0]
    {"WELCOME TO BIT ATM", "SELECT YOUR LANGUAGE", "SECURITY PIN", "ENTER YOUR 4-DIGIT PIN", 
     "MAIN MENU", "CHECK BALANCE", "WITHDRAW CASH", "DEPOSIT CASH", "EXIT", 
     "BALANCE INQUIRY", "YOUR CURRENT BALANCE", "WITHDRAW", "ENTER WITHDRAWAL AMOUNT", 
     "DEPOSIT", "ENTER DEPOSIT AMOUNT", "TRANSACTION SUCCESSFUL", "TRANSACTION FAILED", 
     "THANK YOU FOR USING BIT ATM", "BACK TO MENU", "ERROR"},
    // Kannada [1]
    {"BIT ಎಟಿಎಂಗೆ ಸ್ವಾಗತ", "ನಿಮ್ಮ ಭಾಷೆ ಆಯ್ಕೆ ಮಾಡಿ", "ಸುರಕ್ಷತಾ ಪಿನ್", "ನಿಮ್ಮ 4-ಅಂಕಿಯ ಪಿನ್ ನಮೂದಿಸಿ",
     "ಮುಖ್ಯ ಮೆನು", "ಬ್ಯಾಲೆನ್ಸ್ ಪರಿಶೀಲಿಸಿ", "ಹಣ ಹಿಂಪಡೆಯಿರಿ", "ಹಣ ಠೇವಣಿ", "ನಿರ್ಗಮನ",
     "ಬಾಕಿ ವಿಚಾರಣೆ", "ನಿಮ್ಮ ಪ್ರಸ್ತುತ ಬಾಕಿ", "ಹಿಂಪಡೆಯಿರಿ", "ಹಿಂಪಡೆಯುವ ಮೊತ್ತ ನಮೂದಿಸಿ",
     "ಠೇವಣಿ", "ಠೇವಣಿ ಮೊತ್ತ ನಮೂದಿಸಿ", "ವಹಿವಾಟು ಯಶಸ್ವಿಯಾಗಿದೆ", "ವಹಿವಾಟು ವಿಫಲವಾಗಿದೆ",
     "BIT ಎಟಿಎಂ ಬಳಸಿದ್ದಕ್ಕಾಗಿ ಧನ್ಯವಾದಗಳು", "ಮೆನುಗೆ ಹಿಂತಿರುಗಿ", "ದೋಷ"},
    // Hindi [2]
    {"BIT एटीएम में आपका स्वागत है", "अपनी भाषा चुनें", "सुरक्षा पिन", "अपना 4-अंकीय पिन दर्ज करें",
     "मुख्य मेनू", "बैलेंस जांचें", "नकद निकालें", "नकद जमा करें", "बाहर निकलें",
     "बैलेंस पूछताछ", "आपका वर्तमान बैलेंस", "निकासी", "निकासी राशि दर्ज करें",
     "जमा", "जमा राशि दर्ज करें", "लेन-देन सफल", "लेन-देन विफल",
     "BIT एटीएम का उपयोग करने के लिए धन्यवाद", "मेनू पर वापस जाएं", "त्रुटि"}
};

int main() {
    printf("Content-Type: text/html; charset=UTF-8\n\n");
    
    loadBalance();
    char *query = getenv("QUERY_STRING");
    if (!query) query = "";

    int L = 0;
    if (strstr(query, "L=1")) L = 1;
    else if (strstr(query, "L=2")) L = 2;

    printf("<!DOCTYPE html><html lang='en'><head>"
           "<meta charset='UTF-8'>"
           "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
           "<title>BIT ATM System</title>"
           "<style>"
           "* { margin: 0; padding: 0; box-sizing: border-box; }"
           "body { "
           "  background: linear-gradient(135deg, #0f172a 0%%, #1e293b 100%%); "
           "  color: #fff; "
           "  font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; "
           "  display: flex; "
           "  align-items: center; "
           "  justify-content: center; "
           "  min-height: 100vh; "
           "  margin: 0; "
           "  overflow: hidden; "
           "  position: relative;"
           "}"
           ".money { "
           "  position: absolute; "
           "  color: #0ea5e9; "
           "  font-size: 28px; "
           "  top: -50px; "
           "  z-index: 1; "
           "  animation: rain linear infinite; "
           "  opacity: 0.12; "
           "  pointer-events: none; "
           "  user-select: none; "
           "  font-weight: bold;"
           "}"
           "@keyframes rain { "
           "  to { transform: translateY(110vh) rotate(360deg); } "
           "}"
           ".atm-container { "
           "  width: 950px; "
           "  max-width: 95vw; "
           "  background: #1e293b; "
           "  border: 20px solid #334155; "
           "  border-radius: 30px; "
           "  box-shadow: 0 30px 80px rgba(0,0,0,0.9), inset 0 0 30px rgba(14,165,233,0.05); "
           "  position: relative; "
           "  z-index: 10;"
           "}"
           ".atm-header { "
           "  background: linear-gradient(135deg, #0ea5e9 0%%, #0284c7 100%%); "
           "  padding: 25px; "
           "  text-align: center; "
           "  border-radius: 10px 10px 0 0; "
           "  box-shadow: 0 4px 15px rgba(14,165,233,0.3);"
           "}"
           ".atm-header h1 { "
           "  color: #000; "
           "  font-size: 32px; "
           "  font-weight: 900; "
           "  letter-spacing: 3px; "
           "  text-transform: uppercase; "
           "  text-shadow: 2px 2px 4px rgba(255,255,255,0.3);"
           "}"
           ".atm-body { "
           "  display: flex; "
           "  min-height: 550px;"
           "}"
           ".side-panel { "
           "  width: 140px; "
           "  background: #0f172a; "
           "  display: flex; "
           "  flex-direction: column; "
           "  justify-content: space-around; "
           "  padding: 60px 0; "
           "  border-right: 3px solid #334155;"
           "}"
           ".side-panel.right { "
           "  border-right: none; "
           "  border-left: 3px solid #334155;"
           "}"
           ".physical-btn { "
           "  width: 80px; "
           "  height: 60px; "
           "  background: linear-gradient(145deg, #475569, #1e293b); "
           "  border: 3px solid #0f172a; "
           "  border-radius: 12px; "
           "  margin: 0 auto; "
           "  box-shadow: 0 8px 0 #0f172a, inset 0 2px 5px rgba(255,255,255,0.1); "
           "  position: relative;"
           "}"
           ".physical-btn::after { "
           "  content: ''; "
           "  position: absolute; "
           "  top: 50%%; "
           "  left: 50%%; "
           "  transform: translate(-50%%, -50%%); "
           "  width: 12px; "
           "  height: 12px; "
           "  background: #0ea5e9; "
           "  border-radius: 50%%; "
           "  box-shadow: 0 0 10px #0ea5e9;"
           "}"
           ".screen { "
           "  flex: 1; "
           "  background: #000; "
           "  border: 25px solid #0d1117; "
           "  position: relative; "
           "  overflow: hidden; "
           "  box-shadow: inset 0 0 100px rgba(14,165,233,0.08);"
           "}"
           ".screen-header { "
           "  background: linear-gradient(90deg, #0ea5e9 0%%, #06b6d4 100%%); "
           "  color: #000; "
           "  padding: 20px; "
           "  text-align: center; "
           "  font-size: 22px; "
           "  font-weight: 800; "
           "  letter-spacing: 1.5px; "
           "  text-transform: uppercase; "
           "  box-shadow: 0 3px 10px rgba(14,165,233,0.5);"
           "}"
           ".screen-content { "
           "  padding: 40px 30px; "
           "  min-height: 400px; "
           "  display: flex; "
           "  flex-direction: column; "
           "  justify-content: center; "
           "  align-items: center; "
           "  position: relative;"
           "}"
           ".welcome-section { "
           "  text-align: center; "
           "  width: 100%%;"
           "}"
           ".welcome-section h2 { "
           "  color: #0ea5e9; "
           "  font-size: 28px; "
           "  margin-bottom: 50px; "
           "  font-weight: 600;"
           "}"
           ".lang-options { "
           "  display: flex; "
           "  justify-content: center; "
           "  gap: 25px; "
           "  flex-wrap: wrap;"
           "}"
           ".lang-btn { "
           "  display: inline-block; "
           "  background: linear-gradient(135deg, rgba(14,165,233,0.15) 0%%, rgba(14,165,233,0.05) 100%%); "
           "  border: 3px solid #0ea5e9; "
           "  color: #0ea5e9; "
           "  padding: 20px 40px; "
           "  font-size: 20px; "
           "  font-weight: 700; "
           "  text-decoration: none; "
           "  border-radius: 15px; "
           "  transition: all 0.3s ease; "
           "  min-width: 180px; "
           "  text-align: center;"
           "}"
           ".lang-btn:hover { "
           "  background: linear-gradient(135deg, rgba(14,165,233,0.3) 0%%, rgba(14,165,233,0.15) 100%%); "
           "  transform: translateY(-3px); "
           "  box-shadow: 0 10px 25px rgba(14,165,233,0.4);"
           "}"
           ".pin-section { "
           "  text-align: center; "
           "  width: 100%%;"
           "}"
           ".pin-section h3 { "
           "  color: #94a3b8; "
           "  font-size: 18px; "
           "  margin-bottom: 25px; "
           "  font-weight: 500;"
           "}"
           ".pin-input { "
           "  background: #0f172a; "
           "  border: 4px solid #0ea5e9; "
           "  color: #0ea5e9; "
           "  font-size: 48px; "
           "  text-align: center; "
           "  padding: 20px; "
           "  width: 350px; "
           "  max-width: 90%%; "
           "  border-radius: 15px; "
           "  outline: none; "
           "  letter-spacing: 15px; "
           "  font-weight: 700;"
           "}"
           ".pin-input:focus { "
           "  border-color: #38bdf8; "
           "  box-shadow: 0 0 30px rgba(14,165,233,0.5);"
           "}"
           ".menu-section { "
           "  width: 100%%; "
           "  display: grid; "
           "  grid-template-columns: 1fr 1fr; "
           "  gap: 25px; "
           "  padding: 20px;"
           "}"
           ".menu-option { "
           "  background: linear-gradient(135deg, rgba(14,165,233,0.1) 0%%, rgba(14,165,233,0.05) 100%%); "
           "  border: 3px solid #0ea5e9; "
           "  color: #0ea5e9; "
           "  padding: 30px 25px; "
           "  font-size: 18px; "
           "  font-weight: 700; "
           "  text-decoration: none; "
           "  border-radius: 12px; "
           "  transition: all 0.3s ease; "
           "  text-align: center; "
           "  display: flex; "
           "  align-items: center; "
           "  justify-content: center; "
           "  min-height: 80px;"
           "}"
           ".menu-option:hover { "
           "  background: linear-gradient(135deg, rgba(14,165,233,0.25) 0%%, rgba(14,165,233,0.15) 100%%); "
           "  transform: scale(1.05); "
           "  box-shadow: 0 8px 20px rgba(14,165,233,0.3);"
           "}"
           ".menu-option.exit { "
           "  border-color: #f43f5e; "
           "  color: #f43f5e; "
           "  background: linear-gradient(135deg, rgba(244,63,94,0.1) 0%%, rgba(244,63,94,0.05) 100%%);"
           "}"
           ".menu-option.exit:hover { "
           "  background: linear-gradient(135deg, rgba(244,63,94,0.25) 0%%, rgba(244,63,94,0.15) 100%%);"
           "}"
           ".balance-display { "
           "  text-align: center;"
           "}"
           ".balance-display h3 { "
           "  color: #94a3b8; "
           "  font-size: 20px; "
           "  margin-bottom: 20px;"
           "}"
           ".balance-amount { "
           "  color: #10b981; "
           "  font-size: 64px; "
           "  font-weight: 900; "
           "  margin: 20px 0; "
           "  text-shadow: 0 0 20px rgba(16,185,129,0.3);"
           "}"
           ".transaction-form { "
           "  text-align: center; "
           "  width: 100%%;"
           "}"
           ".transaction-form h3 { "
           "  color: #94a3b8; "
           "  font-size: 20px; "
           "  margin-bottom: 25px;"
           "}"
           ".amount-input { "
           "  background: #0f172a; "
           "  border: 4px solid #0ea5e9; "
           "  color: #0ea5e9; "
           "  font-size: 42px; "
           "  text-align: center; "
           "  padding: 20px; "
           "  width: 400px; "
           "  max-width: 90%%; "
           "  border-radius: 15px; "
           "  outline: none; "
           "  font-weight: 700;"
           "}"
           ".amount-input:focus { "
           "  border-color: #38bdf8; "
           "  box-shadow: 0 0 30px rgba(14,165,233,0.5);"
           "}"
           ".hint-text { "
           "  color: #64748b; "
           "  font-size: 16px; "
           "  margin-top: 15px;"
           "}"
           ".status-message { "
           "  text-align: center; "
           "  padding: 30px;"
           "}"
           ".status-icon { "
           "  font-size: 80px; "
           "  margin-bottom: 20px;"
           "}"
           ".status-title { "
           "  font-size: 32px; "
           "  font-weight: 800; "
           "  margin-bottom: 15px;"
           "}"
           ".status-details { "
           "  font-size: 20px; "
           "  color: #94a3b8; "
           "  margin-top: 10px;"
           "}"
           ".success { color: #10b981; }"
           ".error { color: #f43f5e; }"
           ".back-btn { "
           "  display: inline-block; "
           "  background: linear-gradient(135deg, rgba(100,116,139,0.2) 0%%, rgba(100,116,139,0.1) 100%%); "
           "  border: 3px solid #64748b; "
           "  color: #94a3b8; "
           "  padding: 15px 40px; "
           "  font-size: 18px; "
           "  font-weight: 700; "
           "  text-decoration: none; "
           "  border-radius: 10px; "
           "  margin-top: 30px; "
           "  transition: all 0.3s ease;"
           "}"
           ".back-btn:hover { "
           "  background: linear-gradient(135deg, rgba(100,116,139,0.3) 0%%, rgba(100,116,139,0.2) 100%%); "
           "  transform: translateY(-2px);"
           "}"
           "@media (max-width: 768px) { "
           "  .atm-header h1 { font-size: 24px; } "
           "  .menu-section { grid-template-columns: 1fr; } "
           "}"
           "</style>"
           "</head><body>");

    /* RAIN EFFECT - NOTES AND COINS */
    printf("<script>"
           "const moneyItems = ['💴', '💵', '💶', '💷', '💰', '🪙', '💸'];"
           "setInterval(() => {"
           "  const e = document.createElement('div');"
           "  e.className = 'money';"
           "  e.innerText = moneyItems[Math.floor(Math.random() * moneyItems.length)];"
           "  e.style.left = Math.random() * 100 + 'vw';"
           "  e.style.animationDuration = (Math.random() * 3 + 2) + 's';"
           "  document.body.appendChild(e);"
           "  setTimeout(() => e.remove(), 5000);"
           "}, 150);"
           "</script>");

    printf("<div class='atm-container'>");
    printf("<div class='atm-header'><h1>%s</h1></div>", ui[L][0]);
    printf("<div class='atm-body'>");
    printf("<div class='side-panel'>"
           "<div class='physical-btn'></div>"
           "<div class='physical-btn'></div>"
           "<div class='physical-btn'></div>"
           "<div class='physical-btn'></div>"
           "</div>");
    
    printf("<div class='screen'>");

    // ========== STEP 1: LANGUAGE SELECTION ==========
    if (strlen(query) == 0) {
        printf("<div class='screen-header'>%s</div>", ui[0][1]);
        printf("<div class='screen-content'>"
               "<div class='welcome-section'>");
        printf("<div class='lang-options'>"
               "<a href='?L=0&s=pin' class='lang-btn'>ENGLISH</a>"
               "<a href='?L=1&s=pin' class='lang-btn'>ಕನ್ನಡ</a>"
               "<a href='?L=2&s=pin' class='lang-btn'>हिंदी</a>"
               "</div></div></div>");
    }
    // ========== STEP 2: PIN ENTRY ==========
    else if (strstr(query, "s=pin")) {
        printf("<div class='screen-header'>%s</div>", ui[L][2]);
        printf("<div class='screen-content'>"
               "<div class='pin-section'>"
               "<h3>%s</h3>"
               "<form method='GET' action=''>"
               "<input type='hidden' name='L' value='%d'>"
               "<input type='password' name='p' maxlength='4' pattern='[0-9]{4}' "
               "class='pin-input' placeholder='••••' required autofocus>"
               "</form></div></div>", ui[L][3], L);
    }
    // ========== STEP 3: AUTHORIZED - MAIN MENU ==========
    else if (strstr(query, "p=9876")) {
        
        // ACTION: CHECK BALANCE
        if (strstr(query, "act=bal")) {
            printf("<div class='screen-header'>%s</div>", ui[L][9]);
            printf("<div class='screen-content'>"
                   "<div class='balance-display'>"
                   "<h3>%s</h3>"
                   "<div class='balance-amount'>₹ %.2f</div>"
                   "<a href='?L=%d&p=9876' class='back-btn'>%s</a>"
                   "</div></div>", ui[L][10], amount, L, ui[L][18]);
        }
        // ACTION: WITHDRAW
        else if (strstr(query, "act=with")) {
            char *a = strstr(query, "amt=");
            if (a) {
                float v = atof(a + 4);
                int v_int = (int)v;
                
                printf("<div class='screen-header'>%s</div>", ui[L][11]);
                printf("<div class='screen-content'><div class='status-message'>");
                
                if (v_int <= 0) {
                    printf("<div class='status-icon error'>✗</div>"
                           "<div class='status-title error'>%s</div>"
                           "<div class='status-details'>Invalid Amount Entered</div>", ui[L][16]);
                } else if (v > amount) {
                    printf("<div class='status-icon error'>✗</div>"
                           "<div class='status-title error'>%s</div>"
                           "<div class='status-details'>Available: ₹ %.2f</div>", ui[L][16], amount);
                } else if (v_int % 100 != 0) {
                    printf("<div class='status-icon error'>✗</div>"
                           "<div class='status-title error'>%s</div>"
                           "<div class='status-details'>Only multiples of ₹100 allowed</div>", ui[L][16]);
                } else {
                    amount -= v;
                    saveBalance();
                    logTransaction("Withdraw", v);
                    printf("<div class='status-icon success'>✓</div>"
                           "<div class='status-title success'>%s</div>"
                           "<div class='status-details' style='font-size:26px; color:#10b981; font-weight:900; margin:25px 0; text-transform:uppercase; letter-spacing:2px;'>💵 PLEASE COLLECT YOUR CASH 💵</div>"
                           "<div class='status-details'>Withdrawn Amount: ₹ %.2f</div>"
                           "<div class='status-details'>Remaining Balance: ₹ %.2f</div>", 
                           ui[L][15], v, amount);
                }
                printf("<a href='?L=%d&p=9876' class='back-btn'>%s</a>", L, ui[L][18]);
                printf("</div></div>");
            } else {
                printf("<div class='screen-header'>%s</div>", ui[L][11]);
                printf("<div class='screen-content'>"
                       "<div class='transaction-form'>"
                       "<h3>%s</h3>"
                       "<form method='GET'>"
                       "<input type='hidden' name='L' value='%d'>"
                       "<input type='hidden' name='p' value='9876'>"
                       "<input type='hidden' name='act' value='with'>"
                       "<input type='number' name='amt' class='amount-input' "
                       "placeholder='₹' min='100' step='100' required autofocus>"
                       "<div class='hint-text'>Multiples of ₹100 only</div>"
                       "</form></div></div>", ui[L][12], L);
            }
        }
        // ACTION: DEPOSIT
        else if (strstr(query, "act=dep")) {
            char *a = strstr(query, "amt=");
            if (a) {
                float v = atof(a + 4);
                
                printf("<div class='screen-header'>%s</div>", ui[L][13]);
                printf("<div class='screen-content'><div class='status-message'>");
                
                if (v <= 0) {
                    printf("<div class='status-icon error'>✗</div>"
                           "<div class='status-title error'>%s</div>"
                           "<div class='status-details'>Invalid Amount Entered</div>", ui[L][16]);
                } else {
                    amount += v;
                    saveBalance();
                    logTransaction("Deposit", v);
                    printf("<div class='status-icon success'>✓</div>"
                           "<div class='status-title success'>%s</div>"
                           "<div class='status-details'>Amount Deposited: ₹ %.2f</div>"
                           "<div class='status-details'>New Balance: ₹ %.2f</div>", 
                           ui[L][15], v, amount);
                }
                printf("<a href='?L=%d&p=9876' class='back-btn'>%s</a>", L, ui[L][18]);
                printf("</div></div>");
            } else {
                printf("<div class='screen-header'>%s</div>", ui[L][13]);
                printf("<div class='screen-content'>"
                       "<div class='transaction-form'>"
                       "<h3>%s</h3>"
                       "<form method='GET'>"
                       "<input type='hidden' name='L' value='%d'>"
                       "<input type='hidden' name='p' value='9876'>"
                       "<input type='hidden' name='act' value='dep'>"
                       "<input type='number' name='amt' class='amount-input' "
                       "placeholder='₹' min='1' required autofocus>"
                       "</form></div></div>", ui[L][14], L);
            }
        }
        // MAIN MENU
        else {
            printf("<div class='screen-header'>%s</div>", ui[L][4]);
            printf("<div class='screen-content'>"
                   "<div class='menu-section'>"
                   "<a href='?L=%d&p=9876&act=bal' class='menu-option'>%s</a>"
                   "<a href='?L=%d&p=9876&act=with' class='menu-option'>%s</a>"
                   "<a href='?L=%d&p=9876&act=dep' class='menu-option'>%s</a>"
                   "<a href='?L=%d&act=exit' class='menu-option exit'>%s</a>"
                   "</div></div>", 
                   L, ui[L][5], L, ui[L][6], L, ui[L][7], L, ui[L][8]);
        }
    }
    // ========== STEP 4: EXIT ==========
    else if (strstr(query, "act=exit")) {
        printf("<div class='screen-header'>SESSION ENDED</div>");
        printf("<div class='screen-content'>"
               "<div class='status-message'>"
               "<div class='status-icon success'>✓</div>"
               "<div class='status-title success'>%s</div>"
               "<div class='status-details' style='margin-top:10px;'>Have a great day!</div>"
               "<div class='status-details' style='margin-top:20px; font-size:16px;'>Redirecting...</div>"
               "</div></div>", ui[L][17]);
        printf("<script>setTimeout(() => window.location.href='?', 3000);</script>");
    }
    // ========== ERROR: WRONG PIN ==========
    else {
        printf("<div class='screen-header'>%s</div>", ui[L][19]);
        printf("<div class='screen-content'>"
               "<div class='status-message'>"
               "<div class='status-icon error'>✗</div>"
               "<div class='status-title error'>INVALID PIN</div>"
               "<div class='status-details'>Please try again</div>"
               "<a href='?L=%d&s=pin' class='back-btn'>TRY AGAIN</a>"
               "</div></div>", L);
    }

    printf("</div>");
    printf("<div class='side-panel right'>"
           "<div class='physical-btn'></div>"
           "<div class='physical-btn'></div>"
           "<div class='physical-btn'></div>"
           "<div class='physical-btn'></div>"
           "</div>");
    printf("</div></div>");
    printf("</body></html>");
    
    return 0;
}