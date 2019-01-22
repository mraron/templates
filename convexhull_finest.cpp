
int ccw(pt a, pt b, pt c) {
    b.xx-=a.xx;c.xx-=a.xx;
    b.yy-=a.yy;c.yy-=a.yy;
    
    if(b.yy*c.xx < c.yy*b.xx) {
	return -1;
    }else if(b.yy*c.xx == c.yy*b.xx) {
	return 0;
    }
    
    return 1;
}

ll sqdist(const pt& a, const pt& b) {
    return (a.xx-b.xx)*(a.xx-b.xx)+(a.yy-b.yy)*(a.yy-b.yy);
}

int n;
pt pts[800001];

#define OPT_Q1
#define OPT_Q2

vector<pt> hull() {
    pt orig=pts[0], right_most;
    int orig_ind=0;
    
    for(int i=1;i<n;++i) {
	if(orig.xx==pts[i].xx && orig.yy>pts[i].yy) {
	    orig=pts[i];
	    orig_ind=i;
	} else if(orig.xx>pts[i].xx) {
	    orig=pts[i];
	    orig_ind=i;
	}
    }
    
    int ind=n-1;
    
    swap(pts[ind--], pts[orig_ind]);
    
    #ifdef OPT_Q1
    int bx=0, by=0, sx=0, sy=0;
    #endif
    #ifdef OPT_Q2
    int bxy=0, sxy=0, byx=0, syx=0;
    #endif
    #ifdef OPT_Q1
    pt BX, BY, SX, SY;
    #endif
    #ifdef OPT_Q2
    pt BXY, SXY, BYX, SYX;
    #endif
    for(int i=1;i<n;++i) {
	#ifdef OPT_Q1
	if(pts[bx].xx<pts[i].xx) bx=i;
	if(pts[sx].xx>pts[i].xx) sx=i;
	if(pts[by].yy<pts[i].yy) by=i;
	if(pts[sy].yy>pts[i].yy) sy=i;
	#endif
	#ifdef OPT_Q2
	if(pts[bxy].xx+pts[bxy].yy<pts[i].xx+pts[i].yy) bxy=i;
	if(pts[bxy].xx+pts[bxy].yy>pts[i].xx+pts[i].yy) sxy=i;
	if(pts[byx].yy-pts[byx].xx<pts[i].yy-pts[i].xx) byx=i;
	if(pts[byx].yy-pts[byx].xx>pts[i].yy-pts[i].xx) syx=i;
	#endif
    }
    
    #ifdef OPT_Q1
    BX=pts[bx];
    SX=pts[sx];
    BY=pts[by];
    SY=pts[sy];
    #endif
    
    #ifdef OPT_Q2
    BXY=pts[bxy];
    SXY=pts[sxy];
    BYX=pts[byx];
    SYX=pts[syx];
    #endif
    
    right_most=pts[0];
    for(int i=0;i<=ind;++i) {
	if(ccw(orig, right_most, pts[i])>0) right_most=pts[i];

	#ifdef OPT_Q1
	if(ccw(SX, BY, pts[i])>0 && ccw(BY, BX, pts[i])>0 && ccw(BX, SY, pts[i])>0 && ccw(SY, SX, pts[i])>0) {
	    swap(pts[ind--], pts[i]);
	    i--;
	    continue ;
	}
	#endif
	#ifdef OPT_Q2
	if(ccw(BYX, BXY, pts[i])>0 && ccw(BXY, SYX, pts[i])>0 && ccw(SYX, SXY, pts[i])>0 && ccw(SXY, BYX, pts[i])>0) {
	    swap(pts[ind--], pts[i]);
	    i--;
	    continue ;
	}
	#endif
    }
    
    n=ind+1;
    
    sort(pts, pts+n, [&orig, &right_most](const pt& a, const pt& b) -> bool {
	if(ccw(orig,a,b)==0) {
	    if(ccw(orig, a, right_most)==0)
		return sqdist(orig,a)>sqdist(orig, b);
	    else
		return sqdist(orig,a)<sqdist(orig, b);
	}
	return ccw(orig,a,b)>0;
    });
    
    vector<pt> hull;
    
    hull.pb(orig);
    hull.pb(pts[0]);
    hull.pb(pts[1]);
    
    for(int i=2;i<n;++i) {
	hull.pb(pts[i]);
	while(hull.size()>3 && ccw(hull[hull.size()-3], hull[hull.size()-2], hull[hull.size()-1])<=0) {
	    swap(hull[hull.size()-2], hull[hull.size()-1]);
	    hull.pop_back();
	}
    }
    
    return hull;
}
