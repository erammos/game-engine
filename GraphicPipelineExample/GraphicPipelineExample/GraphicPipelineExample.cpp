#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <cmath>
#include <windows.h>
#include "Matrix.h"


using namespace std;
HWND window;
HDC hdc;
COLORREF *framebuffer;
int width=800;
int height = 600;
RECT actualDesktop;
int PERSP_CORRECT = 1;
 void refresh()
{
	HBITMAP map = CreateBitmap(width, // width. 512 in my case
		height, // heightw
		1, // Color Planes, unfortanutelly don't know what is it actually. Let it be 1
		8 * 4, // Size of memory for one pixel in bits (in win32 4 bytes = 4*8 bits)
		(void*)framebuffer);
	HDC src = CreateCompatibleDC(hdc);
	SelectObject(src, map);
	BitBlt(hdc, // Destination
		0,  // x and
		0,  // y - upper-left corner of place, where we'd like to copy
		width, // width of the region
		height, // height
		src, // source
		0,   // x and
		0,   // y of upper left corner  of part of the source, from where we'd like to copy
		SRCCOPY);
	
	DeleteDC(src);
}

 void putpixel(int x, int y, int c)
 {
	 if (x > width || x < 0) return;
	 if (y > height || y < 0) return;
	 framebuffer[y*width + x] = c;
 }
 void clearBuffer()
 {
	
	memset(framebuffer, 0x0, width * height*sizeof(COLORREF));
 }
 Vec3<double> getViewDirection(double azimuth, double elevation)
 {
	 Vec3<double> dir(cos(elevation)*sin(azimuth), sin(elevation), cos(elevation)*cos(azimuth));
	
	 return dir;
 }

 Matrix44<double> perspTransform(double fov, double aspect,double d_min, double d_max)
 {
	 double u_max = d_min*tan(fov);
	 double r_max = aspect*u_max;
	 double u_min = -u_max;
	 double r_min = -r_max;

	 double InvRdiff = 1.0 / (r_max - r_min);
	 double InvUdiff = 1.0 / (u_max - u_min);
	 double InvDiff = 1.0 / (d_max - d_min);

	 double m[4][4]{
		 { 2.*d_min*InvRdiff,0,0,0},
		 { 0,2.*d_min*InvUdiff,0,0 },
		 { -(r_max+r_min)*InvRdiff,-(u_max + u_min)*InvUdiff,d_max*InvDiff,1 },
		 { 0,0,-d_max*d_min*InvDiff,0 } };

	 Matrix44 <double> vt(m);
	 return vt;

 }
 Matrix44<double> orthoTransform(double r_min,double r_max,double u_min, double u_max,double d_min, double d_max)
 {


	 double m[4][4]{
		 { 2 / (r_max - r_min),0,0,0 },
		 { 0,2 / (u_max - u_min),0,0 },
		 { 0,0,1 / (d_max - d_min),0 },
		 { -((r_max + r_min) / (r_max - r_min))
		 ,-((u_max + u_min) / (u_max - u_min))
		 ,-((d_min) / (d_max - d_min)),1  } };

	 Matrix44 <double> vt(m);
	 return vt;
	
 }

 Matrix44<double> viewTransform(Vec3<double> eye, Vec3<double> u, Vec3<double> dir)
 {
	 dir.normalize();
	 u.normalize();
	 Vec3<double>r = dir.cross(u);
	

	 double m[4][4]{
		 { r.x,u.x,dir.x,0 },
		 { r.y,u.y,dir.y,0 },
		 { r.z,u.z,dir.z,0 },
		 { -r.dot(eye),-u.dot(eye),-dir.dot(eye),1 } };

	 Matrix44 <double> vt(m);


	 return vt;

 }
Matrix44<double> viewTransform(Vec3<double> eye,double azimuth,double elevation)
 {
	 Vec3<double> dir=getViewDirection(azimuth, elevation);
	 Vec3<double> u(0, 1 ,0);
	 Vec3<double>r = u.cross(dir);
	 u = dir.cross(r);
	


	 double m[4][4]{ 
	 { r.x,u.x,dir.x,0 }, 
	 { r.y,u.y,dir.y,0 },
	 { r.z,u.z,dir.z,0 },
	 { -r.dot(eye),-u.dot(eye),-dir.dot(eye),1 } };
	
	 Matrix44 <double> vt(m);
	

	 return vt;
	
 }
 void bhm_line(int x1, int y1, int x2, int y2, int c)
 {
	 int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	 dx = x2 - x1;
	 dy = y2 - y1;
	 dx1 = fabs(dx);
	 dy1 = fabs(dy);
	 px = 2 * dy1 - dx1;
	 py = 2 * dx1 - dy1;
	 if (dy1 <= dx1)
	 {
		 if (dx >= 0)
		 {
			 x = x1;
			 y = y1;
			 xe = x2;
		 }
		 else
		 {
			 x = x2;
			 y = y2;
			 xe = x1;
		 }
		 putpixel(x, y, c);
		 for (i = 0; x < xe; i++)
		 {
			 x = x + 1;
			 if (px < 0)
			 {
				 px = px + 2 * dy1;
			 }
			 else
			 {
				 if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
				 {
					 y = y + 1;
				 }
				 else
				 {
					 y = y - 1;
				 }
				 px = px + 2 * (dy1 - dx1);
			 }
			 
			 putpixel(x, y, c);
		 }
	 }
	 else
	 {
		 if (dy >= 0)
		 {
			 x = x1;
			 y = y1;
			 ye = y2;
		 }
		 else
		 {
			 x = x2;
			 y = y2;
			 ye = y1;
		 }
		 putpixel(x, y, c);
		 for (i = 0; y < ye; i++)
		 {
			 y = y + 1;
			 if (py <= 0)
			 {
				 py = py + 2 * dx1;
			 }
			 else
			 {
				 if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
				 {
					 x = x + 1;
				 }
				 else
				 {
					 x = x - 1;
				 }
				 py = py + 2 * (dx1 - dy1);
			 }
			 
			 putpixel(x, y, c);
		 }
	 }
 }
 Vec3<double> mapToScreen(Vec3<double> projP)
 {
	 double Ax = ((1 + projP.x) / 2)*width;
	 double Ay = height-((1 + projP.y) / 2)*height;
	 return Vec3<double>(Ax, Ay, projP.z,projP.w);
 }

 int x, y, z = 0;


 //Vec3<double> pointA(-256.0, 256.0, 256);
 //Vec3<double> pointB(256.0, -256.0, 256);
 //Vec3<double> rect[8]{
	  //Vec3<double>(-1,1,0),Vec3<double>(1,1,0) ,Vec3<double>(-1,1,1) ,Vec3<double>(1,1,1) ,
	 // Vec3<double>(-1,0,0) ,Vec3<double>(1,0,0) ,Vec3<double>(-1,0,1) ,Vec3<double>(1,0,1) };
 inline
	 float edgeFunction(const Vec3<double> &a, const Vec3<double> &b, const Vec3<double> &c)
 {
	 return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
 }
 Vec3<double> rect[3]{
	 Vec3<double>(13.,34.,114.),Vec3<double>(29.,-15.,44.),Vec3<double>(-48.,-10.,82.) };

 void renderTriangle(Vec3<double> &v0,  Vec3<double> &v1,  Vec3<double> &v2, COLORREF c0, COLORREF c1, COLORREF c2, Vec3<double>st0, Vec3<double>st1, Vec3<double>st2)
 {

	v0.x = v0.x / v0.w;
	v0.y = v0.y / v0.w;
	v0.z = v0.z / v0.w;

	v1.x = v1.x / v1.w;
	v1.y = v1.y / v1.w;
	v1.z = v1.z / v1.w;

	v2.x = v2.x / v2.w;
	v2.y = v2.y / v2.w;
	v2.z = v2.z / v2.w;

	 v0.w = 1 / v0.w;
	 v1.w = 1 / v1.w;
	 v2.w = 1 / v2.w;

	 v0 = mapToScreen(v0);
	 v1 = mapToScreen(v1);
	 v2 = mapToScreen(v2);

	 for (uint32_t j = 0; j < height; ++j) {
		 for (uint32_t i = 0; i < width; ++i) {
			 Vec3<double> p(i + 0.5f, j + 0.5f,0);
		

			 double s0 = edgeFunction(v1, v2, p);
			 double s1 = edgeFunction(v2, v0, p);
			 double s2 = edgeFunction(v0, v1, p);
			 if (s0 <= 0 && s1 <= 0 && s2 <= 0) {

				 double area = edgeFunction(v0, v1, v2);
				 
				 s0 /= area;
				 s1 /= area;
				 s2 /= area;
				 float r = s0 * (GetRValue(c0)/255.f)*v0.w + s1 * (GetRValue(c1)/255.f) *v1.w + s2 * (GetRValue(c2)/255.f) * v2.w;
				 float g = s0 * (GetGValue(c0)/255.f)*v0.w + s1 * (GetGValue(c1)/255.f) * v1.w + s2 * (GetGValue(c2)/255.f) * v2.w;
				 float b = s0 * (GetBValue(c0) /255.f)*v0.w + s1 * (GetBValue(c1)/255.f) * v1.w + s2 * (GetBValue(c2)/255.f) * v2.w;

				// float s = w0 * st0.x + w1 * st1.x + w2 * st2.x;
				 //float t = w0 * st0.y + w1 * st1.y + w2 * st2.y;	
					 // put this on z-buffer;
				double w= 1/(s0 * v0.w + s1 *v1.w + s2 *v2.w);		
				r *= w, g *= w, b *= w;
					 //s *= z, t *= z;
					 
				  
				 putpixel(i, j, RGB(r*255, g*255, b*255));
		
			 }
		 }
	 }
 }
 void GetDesktopResolution(int& horizontal, int& vertical)
 {   
	 RECT desktop;
	 // Get a handle to the desktop window
	 const HWND hDesktop = GetDesktopWindow();
	 // Get the size of screen to the variable desktop
	 GetWindowRect(hDesktop, &desktop);
	 // The top left corner will have coordinates (0,0)
	 // and the bottom right corner will have coordinates
	 // (horizontal, vertical)
	 horizontal = desktop.right;
	 vertical = desktop.bottom;
 }

 DWORD WINAPI Render(LPVOID lpParam)
 {
	 Sleep(1000);
	 while (!GetAsyncKeyState(VK_ESCAPE))
	 {
		 long long time = GetTickCount();
		 clearBuffer();
		

		 if (GetAsyncKeyState(VK_LEFT)) x--;
		 if (GetAsyncKeyState(VK_RIGHT))x++;
		 if (GetAsyncKeyState(VK_UP)) z++;
		 if (GetAsyncKeyState(VK_DOWN)) z--;
		 if (GetAsyncKeyState(VK_SPACE))
		 {
			 if (PERSP_CORRECT) PERSP_CORRECT = 0; else PERSP_CORRECT = 1;
		 }

		 Matrix44<double> viewT = viewTransform(Vec3<double>(x, y, z), 0, 0);
		// Matrix44<double> viewT = viewTransform(Vec3<double>(2.5 +x, 3+y,3.5+z), Vec3<double>(-1., -1., 2.), Vec3<double>(-1., -1., -1.));

		 //Matrix44<double> orthoT = orthoTransform(-100, 100, -500, 500, 0, 500);
		 Matrix44<double> persT = perspTransform(M_PI / 6,(double)width/height, 1., 200.);
		
		
		 Matrix44<double> rotate;
		 rotate=rotate.rotateZ(M_PI / 2);

		 double t[4][4]{
			 { 1.,0,0,0 },
			 { 0,1.,0,0 },
			 { 0,0,1.,0 },
			 { 1.,1.,1.,1 } };

		 Matrix44<double> translate(t);
		 Matrix44<double> viewPers =viewT*persT;
		

		// cout << "projA:" << projA.toString();
		 //cout << " projB:" << projB.toString() << endl;

		
		 Vec3<double> clip_points[4];
		 for (int i = 0; i < 3; i++)
		 {
			 clip_points[i] = viewPers.transformPoint(rect[i]);
		 }
		// cout << "A:" << A.toString();
		// cout << "B:" << B.toString();

		// bhm_line(0, 0, 511, 511, 0xff);
		// system("cls");
		// cout << "projA:" << rect_proj[0].toString();
		 //cout << "projB:" << rect_proj[1].toString();
		 //cout << "projC:" << rect_proj[2].toString();
		
		 renderTriangle(clip_points[0], clip_points[1], clip_points[2],0xff0000, 0x00ff00, 0x0000ff,Vec3<double>(0,1,0), Vec3<double>(1, 0, 0), Vec3<double>(0, 0, 0));
		// bhm_line(rect_proj[0].x, rect_proj[0].y, rect_proj[1].x, rect_proj[1].y, 0xffff00);
		// bhm_line(rect_proj[1].x, rect_proj[1].y, rect_proj[2].x, rect_proj[2].y, 0xffff00);
		 //bhm_line(rect_proj[2].x, rect_proj[2].y, rect_proj[0].x, rect_proj[0].y, 0xffff00);
		


		 //bhm_line(A.x, A.y, B.x, B.y, 0xffff00);
		// bhm_line(A.x, A.y, B.x, B.y, 0xffff00);
		// bhm_line(A.x, A.y, B.x, B.y, 0xffff00);

		 refresh();
		// std::cout << GetTickCount() - time << "ms" << endl;
		 
	 }

	 return 0;
 }
 void ErrorHAndler(LPTSTR lpszFunction)
 {

 }
 
int main()
{
	//GetDesktopResolution(width, height);
	window = GetActiveWindow(); 
	hdc = GetDC(window);
	framebuffer = (COLORREF*)calloc(width * height, sizeof(COLORREF));	
	GetWindowRect(GetDesktopWindow(), &actualDesktop);
	
	HANDLE thread = CreateThread(NULL, 0, Render, NULL, 0, NULL);
	if (thread)
	{
		WaitForSingleObject(thread, INFINITE);
	}
	return 0;
}