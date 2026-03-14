#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

/* ================= DATA ================= */
struct Service {
    int id;
    char owner[30];
    char service[20];
    int bill;
    char status[20];
};

struct Service s[50];
int count = 0;

/* ================= OPEN HTML ================= */
void openHTML(const char *file) {
#ifdef _WIN32
    char cmd[200];
    sprintf(cmd, "start %s", file);
#else
    char cmd[200];
    sprintf(cmd, "xdg-open %s", file);
#endif
    system(cmd);
}

/* ================= LOGIN PAGE ================= */
void loginPage() {
    FILE *fp = fopen("login.html", "w");

    fprintf(fp,
"<!DOCTYPE html>\n"
"<html lang='en'>\n"
"<head>\n"
"<meta charset='UTF-8'>\n"
"<title>Login</title>\n"
"<style>\n"
"body{margin:0;height:100vh;display:flex;align-items:center;justify-content:center;"
"background:#020617;font-family:Arial;color:white}\n"
".box{background:rgba(255,255,255,0.08);padding:30px;border-radius:20px;width:360px}\n"
"input{width:100%%;padding:12px;margin:10px 0;border:none;border-radius:10px;"
"background:#111827;color:white}\n"
"button{width:100%%;padding:12px;border:none;border-radius:10px;"
"background:linear-gradient(90deg,#38bdf8,#a855f7);color:white;font-weight:bold}\n"
"</style>\n"
"</head>\n"
"<body>\n"
"<div class='box'>\n"
"<h2 style='text-align:center'>Service Login</h2>\n"
"<form onsubmit='return loginCheck()'>\n"
"<input type='text' id='user' placeholder='Username' required>\n"
"<input type='email' id='mail' placeholder='Email' required>\n"
"<input type='password' id='pass' placeholder='Password' required>\n"
"<button type='submit'>Login</button>\n"
"</form>\n"
"<p style='font-size:12px;text-align:center'>admin | admin@gmail.com | 123456</p>\n"
"</div>\n"
"<script>\n"
"function loginCheck(){\n"
"  var u = document.getElementById('user').value.trim();\n"
"  var e = document.getElementById('mail').value.trim();\n"
"  var p = document.getElementById('pass').value.trim();\n"
"  if(u === 'admin' && e === 'admin@gmail.com' && p === '123456'){\n"
"    document.body.innerHTML = '<h1 style=\"text-align:center;margin-top:40vh;color:#22c55e\">Login Successful ✅<br><small>Return to terminal and press ENTER</small></h1>';\n"
"  } else {\n"
"    alert('Invalid Credentials');\n"
"  }\n"
"  return false;\n"
"}\n"
"</script>\n"
"</body>\n"
"</html>"
    );

    fclose(fp);
    openHTML("login.html");

    printf("\n✔ Login page opened in browser\n");
    printf("✔ After SUCCESSFUL login, press ENTER here\n");
    getchar();
}

/* ================= ADD SERVICE ================= */
void addService() {
    printf("Service ID: ");
    scanf("%d",&s[count].id);

    printf("Owner Name: ");
    scanf("%s",s[count].owner);

    int c;
    printf("1.General 2.Oil 3.Full : ");
    scanf("%d",&c);

    if(c==1){ strcpy(s[count].service,"General"); s[count].bill=500; }
    if(c==2){ strcpy(s[count].service,"Oil"); s[count].bill=300; }
    if(c==3){ strcpy(s[count].service,"Full"); s[count].bill=1000; }

    strcpy(s[count].status,"Pending");
    count++;
}

/* ================= VIEW SERVICES IN BROWSER ================= */
void viewServicesHTML() {
    FILE *fp = fopen("services.html", "w");

    fprintf(fp,
"<!DOCTYPE html>\n<html lang='en'>\n<head>\n<meta charset='UTF-8'>\n"
"<title>All Services</title>\n<style>"
"body{font-family:Arial;text-align:center;background:#f0f4f8;}"
"h2{color:#1e3a8a;margin-top:20px;}"
"table{border-collapse:collapse;width:80%%;margin:auto;}"
"th,td{border:1px solid #000;padding:10px;text-align:center;}"
"th{background-color:#4ade80;color:white;}"
"tr:nth-child(even){background-color:#e2e8f0;}"
".Pending{background-color:#fde68a;}"      // Yellow
".InProgress{background-color:#60a5fa;}"   // Blue
".Completed{background-color:#22c55e;color:white;}" // Green
"</style>\n</head>\n<body>\n"
"<h2>All Services</h2>\n"
"<table>\n<tr><th>ID</th><th>Owner</th><th>Service</th><th>Bill</th><th>Status</th></tr>\n"
    );

    for(int i=0; i<count; i++) {
        fprintf(fp,
            "<tr class='%s'><td>%d</td><td>%s</td><td>%s</td><td>%d</td><td>%s</td></tr>\n",
            s[i].status, s[i].id, s[i].owner, s[i].service, s[i].bill, s[i].status
        );
    }

    fprintf(fp, "</table>\n</body>\n</html>");
    fclose(fp);

    openHTML("services.html"); // Opens in browser
}

/* ================= UPDATE STATUS ================= */
void updateStatus() {
    int id;
    printf("Enter Service ID: ");
    scanf("%d",&id);

    for(int i=0;i<count;i++){
        if(s[i].id==id){
            int c;
            printf("1.Pending 2.InProgress 3.Completed : ");
            scanf("%d",&c);
            if(c==1) strcpy(s[i].status,"Pending");
            if(c==2) strcpy(s[i].status,"InProgress");
            if(c==3) strcpy(s[i].status,"Completed");
            return;
        }
    }
    printf("Service not found\n");
}

/* ================= MAIN ================= */
int main() {
    int ch;

    loginPage();   // LOGIN FIRST

    do {
        printf("\n1.Add Service\n2.View Services (Browser)\n3.Update Status\n4.Exit\nChoice: ");
        scanf("%d",&ch);

        if(ch==1) addService();
        if(ch==2) viewServicesHTML();
        if(ch==3) updateStatus();

    } while(ch!=4);

    return 0;
}
