#ifndef project
#define project
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <iostream>
using namespace std;
//Variable types...
typedef double Flt;
typedef Flt Vec[3];
typedef Vec Mat[3];
void vecMake(Flt,Flt,Flt,Vec);
#define rnd() ((Flt)rand() / (Flt)RAND_MAX)
//constant definitions...
const int MAXOBJECTS =  1000;
const int MAXLIGHTS = 1000;
enum {
    TYPE_NONE=0,
    TYPE_DISK,
    TYPE_RING,
    TYPE_SPHERE,
    TYPE_TRIANGLE,
    TYPE_CYLINDER,
    TYPE_CONE,
    TYPE_IMG,
    ORTHO,
    PERSPECTIVE,
    SURF_NONE,
    SURF_CHECKER,
    SURF_NOISE,
    SURF_NOISE2

};

//Ray tracing structures
struct Ray {
    //Ray origin and direction
    Vec o, d;
};

struct Hit {
    //t     = distance to hit point
    //p     = hit point
    //norm  = normal of surface hit
    //color = color of surface hit
    Flt t;
    Vec p, norm, color;
};

struct Object {
    int type;
    Vec center;
    Vec norm;
    Mat m[3];
    Vec tri[3];
    Flt radius, radius2;
    Vec color;
    int surface;
    bool inside;
    bool specular;
    bool texture;
    bool Dtex;
    bool atex;
    bool btext;
    bool btex;
    bool back;
    bool bground;
    bool bground2;
    bool g;
    bool gg;
    bool gordon;
    bool gordinos;
    bool gordon1;
    bool gordinos1;
    bool gordon2;
    bool gordinos2;
    Vec spec;
    Flt base, apex;
    Object() {
        specular = false;
        inside = false;
        texture = false;
        back = false;
        atex = false;
        btext = false;
        Dtex = false;
        btex = false;
        bground = false;
        bground2 = false;
	g = false;
	gg = false;
        gordon = false;
        gordinos = false;
        gordon1 = false;
        gordinos1 = false;
        gordon2 = false;
        gordinos2 = false;
        vecMake(1.0, 1.0, 1.0, spec);
    }
};

extern class Global {
    public:
        int xres, yres, zres;
        int mode;
        Object object[MAXOBJECTS];
        int nobjects;
        int color;
        int tilt;
        int checker;
        int saturn;
        int initials;
        int nimg;
        int nlights;
	bool gordons;
	bool gordon1;
	bool gordon2;
        Vec ambient;
        Vec diffuse;
        Vec sky[2];
        Vec lightPos[MAXLIGHTS];
        Vec lightColor[MAXLIGHTS];
        Vec from, at, up;
        Flt angle;
        Global() {
            srand((unsigned)time(NULL));
            xres = 640, yres = 480, zres = 720;
            mode = 0;
            nobjects = 0;
            color = 0;
            tilt = 0;
            checker = 0;
            saturn = 0;
            initials = 0;
            nimg = 0;
            nlights = 0;
	    gordons = 0;
            vecMake(.2,.2,.2,ambient);
            vecMake(.8,.8,.8,diffuse);
            vecMake(.7,.7,.7,sky[0]);
            vecMake(.2,.1,.3,sky[1]);
            vecMake(-100.0,500,-1000,lightPos[0]);
            vecMake(-100.0,500,-1000,lightColor[0]);
            nlights = 0;
            vecMake(4.0, 250.0, 800.0, from);
            vecMake(0.0, 0.0, 0.0, at);
            vecMake(0.0, 1.0, 0.0, up);
            angle = 30.0;
        }
} g;

extern class Image {
    public:
        int width, height, width2, height2;
        Image *img;
        Object *  o;
        unsigned char* data;
        ~Image() { delete [] data;}
        Image() {
            system("convert project.jpg project.ppm");
            FILE *fpi = fopen("project.ppm", "r");
            if (fpi) {
                char line[200];
                fgets(line, 200, fpi);
                fgets(line, 200, fpi);
                while (line[0] == '#')
                    fgets(line, 200, fpi);
                sscanf(line, "%i %i", &width, &height);
                fgets(line, 200, fpi);
                //get pixel data;
                int n = (width * height * 3);
                data = new unsigned char[n];
                for (int i = 0; i < n; i++) {
                    data[i] = fgetc(fpi);
                }
                fclose(fpi);
            }

            unlink("project.ppm");
        }

} img;

extern class Im {
    public:
        int width, height, width2, height2;
        Im *img;
        Object *  o;
        unsigned char* data;
        ~Im() { delete [] data;}
        Im() {
            system("convert project4.jpg project4.ppm");
            FILE *fpi = fopen("project4.ppm", "r");
            if (fpi) {
                char line[200];
                fgets(line, 200, fpi);
                fgets(line, 200, fpi);
                while (line[0] == '#')
                    fgets(line, 200, fpi);
                sscanf(line, "%i %i", &width, &height);
                fgets(line, 200, fpi);
                //get pixel data;
                int n = (width * height * 3);
                data = new unsigned char[n];
                for (int i = 0; i < n; i++) {
                    data[i] = fgetc(fpi);
                }
                fclose(fpi);
            }

            unlink("project4.ppm");
        }

} img4;


extern class Imag {
    public:
        int width, height, width2, height2;
        Imag *img;
        Object *  o;
        unsigned char* data;
        ~Imag() { delete [] data;}
        Imag() {
            system("convert project2.jpg project2.ppm");
            FILE *fpi = fopen("project2.ppm", "r");
            if (fpi) {
                char line[200];
                fgets(line, 200, fpi);
                fgets(line, 200, fpi);
                while (line[0] == '#')
                    fgets(line, 200, fpi);
                sscanf(line, "%i %i", &width, &height);
                fgets(line, 200, fpi);
                //get pixel data;
                int n = width * height * 3;
                data = new unsigned char[n];
                for (int i = 0; i < n; i++) {
                    data[i] = fgetc(fpi);
                }
                fclose(fpi);
            }

            unlink("project2.ppm");
        }

} img2;

extern class Imae {
    public:
        int width, height, width2, height2;
        Imae *img;
        Object *  o;
        unsigned char* data;
        ~Imae() { delete [] data;}
        Imae() {
            system("convert project3.jpg project3.ppm");
            FILE *fpi = fopen("project3.ppm", "r");
            if (fpi) {
                char line[200];
                fgets(line, 200, fpi);
                fgets(line, 200, fpi);
                while (line[0] == '#')
                    fgets(line, 200, fpi);
                sscanf(line, "%i %i", &width, &height);
                fgets(line, 200, fpi);
                //get pixel data;
                int n = width * height * 3;
                data = new unsigned char[n];
                for (int i = 0; i < n; i++) {
                    data[i] = fgetc(fpi);
                }
                fclose(fpi);
            }

            unlink("project3.ppm");
        }

} img3;

extern class Ima {
    public:
        int width, height, width2, height2;
        Ima *img;
        Object *  o;
        unsigned char* data;
        ~Ima() { delete [] data;}
        Ima() {
            system("convert project5.jpg project5.ppm");
            FILE *fpi = fopen("project5.ppm", "r");
            if (fpi) {
                char line[200];
                fgets(line, 200, fpi);
                fgets(line, 200, fpi);
                while (line[0] == '#')
                    fgets(line, 200, fpi);
                sscanf(line, "%i %i", &width, &height);
                fgets(line, 200, fpi);
                //get pixel data;
                int n = width * height * 3;
                data = new unsigned char[n];
                for (int i = 0; i < n; i++) {
                    data[i] = fgetc(fpi);
                }
                fclose(fpi);
            }

            unlink("project5.ppm");
        }

} img5;

extern class photo {
    public:
        int width, height, width2, height2;
        photo *img;
        Object *  o;
        unsigned char* data;
        ~photo() { delete [] data;}
        photo() {
            system("convert project6.jpg project6.ppm");
            FILE *fpi = fopen("project6.ppm", "r");
            if (fpi) {
                char line[200];
                fgets(line, 200, fpi);
                fgets(line, 200, fpi);
                while (line[0] == '#')
                    fgets(line, 200, fpi);
                sscanf(line, "%i %i", &width, &height);
                fgets(line, 200, fpi);
                //get pixel data;
                int n = (width * height * 3);
                data = new unsigned char[n];
                for (int i = 0; i < n; i++) {
                    data[i] = fgetc(fpi);
                }
                fclose(fpi);
            }

            unlink("project6.ppm");
        }

} pic;


extern class phot {
    public:
        int width, height, width2, height2;
        phot *img;
        Object *  o;
        unsigned char* data;
        ~phot() { delete [] data;}
        phot() {
            system("convert project7.jpg project7.ppm");
            FILE *fpi = fopen("project7.ppm", "r");
            if (fpi) {
                char line[200];
                fgets(line, 200, fpi);
                fgets(line, 200, fpi);
                while (line[0] == '#')
                    fgets(line, 200, fpi);
                sscanf(line, "%i %i", &width, &height);
                fgets(line, 200, fpi);
                //get pixel data;
                int n = (width * height * 3);
                data = new unsigned char[n];
                for (int i = 0; i < n; i++) {
                    data[i] = fgetc(fpi);
                }
                fclose(fpi);
            }

            unlink("project7.ppm");
        }

} pic1;


extern class pho {
    public:
        int width, height, width2, height2;
        pho *img;
        Object *  o;
        unsigned char* data;
        ~pho() { delete [] data;}
        pho() {
            system("convert project8.jpg project8.ppm");
            FILE *fpi = fopen("project8.ppm", "r");
            if (fpi) {
                char line[200];
                fgets(line, 200, fpi);
                fgets(line, 200, fpi);
                while (line[0] == '#')
                    fgets(line, 200, fpi);
                sscanf(line, "%i %i", &width, &height);
                fgets(line, 200, fpi);
                //get pixel data;
                int n = (width * height * 3);
                data = new unsigned char[n];
                for (int i = 0; i < n; i++) {
                    data[i] = fgetc(fpi);
                }
                fclose(fpi);
            }

            unlink("project8.ppm");
        }

} pic2;


extern class X11_wrapper {
    private:
        Display *dpy;
        Window win;
        GC gc;
    public:
        X11_wrapper() {
            //constructor
            if (!(dpy=XOpenDisplay(NULL))) {
                fprintf(stderr, "ERROR: could not open display\n");
                fflush(stderr);
                exit(EXIT_FAILURE);
            }
            int scr = DefaultScreen(dpy);
            win = XCreateSimpleWindow(dpy, RootWindow(dpy, scr), 1, 1,
                    g.xres, g.yres, 0, 0x00ffffff, 0x00000000);
            XStoreName(dpy, win, "3480 ray tracer.  Press M for menu.");
            gc = XCreateGC(dpy, win, 0, NULL);
            XMapWindow(dpy, win);
            XSelectInput(dpy, win, ExposureMask | StructureNotifyMask |
                    PointerMotionMask | ButtonPressMask |
                    ButtonReleaseMask | KeyPressMask);
        }
        ~X11_wrapper() {
            XDestroyWindow(dpy, win);
            XCloseDisplay(dpy);
        }
        void getWindowAttributes(int *width, int *height) {
            XWindowAttributes gwa;
            XGetWindowAttributes(dpy, win, &gwa);
            *width = gwa.width;
            *height = gwa.height;
        }
        XImage *getImage(int width, int height) {
            //XImage *image = XGetImage(dpy, win,
            //            0, 0 , width, height, AllPlanes, ZPixmap);
            return XGetImage(dpy, win, 0, 0, width, height, AllPlanes, ZPixmap);
        }
        void checkResize(XEvent *e) {
            //ConfigureNotify is sent when window size changes.
            if (e->type != ConfigureNotify)
                return;
            XConfigureEvent xce = e->xconfigure;
            g.xres = xce.width;
            g.yres = xce.height;
        }
        void clearScreen() {
            //XClearWindow(dpy, win);
            setColor3i(0,0,0);
            XFillRectangle(dpy, win, gc, 0, 0, g.xres, g.yres);
        }
        bool getXPending() {
            return (XPending(dpy));
        }
        void getXNextEvent(XEvent *e) {
            XNextEvent(dpy, e);
        }
        void setColor3i(int r, int g, int b) {
            unsigned long cref = (r<<16) + (g<<8) + b;
            XSetForeground(dpy, gc, cref);
        }
        void drawImage(Image *img, int x, int y) {
            //center Image in window
            int xoffset = img->width/2;
            int yoffset = img->height/2;

            for (int i = 0; i < img->height; i++) {
                for(int j = 0; j < img->width; j++) {
                    int r1 = img->data[i*img->width*3 + j*3 + 0];
                    int g1 = img->data[i*img->width*3 + j*3 + 1];
                    int b1 = img->data[i*img->width*3 + j*3 + 2];
                    setColor3i(r1 , g1, b1);
                    XDrawPoint(dpy, win, gc, i - xoffset, j -yoffset);

                }
            }
        }
        unsigned long rgbToLong(Vec rgb) {
            //Convert rgb[3] into an integer
            const float range = 255.999;
            int i;
            unsigned long cref = 0;
            for (i=0; i<3; i++) {
                //Don't let a color get too bright.
                if (rgb[i] > 1.0)
                    rgb[i] = 1.0;
                //Shift left 8 bits
                cref <<= 8;
                //Put next color component in low-order byte
                cref += (int)(rgb[i]*range);
            }
            return cref;
        }
        void drawPixel(int x, int y, Vec rgb) {
            unsigned long cref = rgbToLong(rgb);
            XSetForeground(dpy, gc, cref);
            XDrawPoint(dpy, win, gc, x, y);
        }
        void drawText(int x, int y, const char *text) {
            XDrawString(dpy, win, gc, x, y, text, strlen(text));
        }
} x11;
#endif
