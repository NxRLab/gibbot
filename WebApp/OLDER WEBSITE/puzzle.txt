var ur = document.location.href;
var level = 1;
if ( ur.indexOf("?") != -1 ){
var a = ur.split("=");
var level = a[1];
} 
else
{
   document.getElementById("lev1").checked=true;
}
if(level==1)
{
   document.getElementById("lev1").checked=true;
}
else if(level==2)
{
   document.getElementById("lev2").checked=true;
}   
if(level==1)
{ 
   document.getElementById("lev1").checked=true;   
   document.write("<table border=0 cellpadding=1>");
   document.write("<tr>");
   document.write('<td> <img name=i0 width=30px height=30px src="" onclick=moves(0)></td>');
   document.write('<td> <img name=i1 width=30px height=30px src="" onclick=moves(1)></td>');
   document.write('<td> <img name=i2 width=30px height=30px src="" onclick=moves(2)></td>');
   document.write("</tr>");
   document.write("<tr>");
   document.write('<td> <img name=i3 width=30px height=30px src="" onclick=moves(3)></td>');
   document.write('<td> <img name=i4 width=30px height=30px src="" onclick=moves(4)></td>');
   document.write('<td> <img name=i5 width=30px height=30px src="" onclick=moves(5)></td>');
   document.write("</tr>");
   document.write("<tr>");
   document.write('<td> <img name=i6 width=30px height=30px src="" onclick=moves(6)></td>');
   document.write('<td> <img name=i7 width=30px height=30px src="" onclick=moves(7)></td>');
   document.write('<td> <img name=i8 width=30px height=30px src="" onclick=moves(8)></td>');
   document.write("</tr>");
   document.write("</table>");
 
    Array.prototype.inArray = function (value)
    {  
      var i;
      for (i=0; i < this.length; i++) 
      {
        if (this[i] == value) 
        {
            return true;
        }    
      }   
       return false;
    };
  
     var xx;
     xx=9;
     var jj = new Array();
     while(xx>0)
     {
        var ff = Math.round(Math.random()*8);
        if(!jj.inArray(ff))
        {
          jj[jj.length] = ff;
          xx=xx-1;
        } 
      } 
      for(var ffg=0; ffg<jj.length; ffg++)
      {
        var g = jj[ffg];
        var p = eval("document.images.i"+ffg);
        p.src ="images1/"+g+".gif";
      }
      function swap(x1,x2)
      {
        var temp=jj[x1];
        jj[x1]=jj[x2];
        jj[x2]=temp;
        var p = eval("document.images.i"+x1);
        p.src="images1/"+jj[x1]+".gif";
        p = eval("document.images.i"+x2);
        p.src="images1/"+jj[x2]+".gif";
      }
       var firstmove=1;
       var t=0;
       function tim()
       {
         frm.txt1.value=t; 
         t=t+1;
         ti= setTimeout("tim()",1000);
       }
       function moves(a)
       {
          var moved=false;
          if(a%3 !=0)
          {
            if(jj[a-1]==0)
            {
               moved=true;
               if(moved==true)
               {
                   val=firstmove++;
                   frm.txt.value=val;
               }
               swap(a-1,a);
             }
           } 
           if((a+1)%3 !=0 && moved==false)
           {
              if(jj[a+1]==0)
              {
                 moved=true;
                 if(moved==true)
                 {
                    val=firstmove++;
                    frm.txt.value=val;
                 }
               swap(a+1,a);
             }   
           }  
           if(a > 2 && moved==false)
           {
             if(jj[a-3]==0)
             {
                moved=true;
                if(moved==true)
                {
                   val=firstmove++;
                   frm.txt.value=val;
                }
                 swap(a-3,a);
              }   
           }  
           if(a < 6 && moved==false)
           {
             if(jj[a+3]==0)
             {
                 moved=true;
                 if(moved==true)
                 {
                    val=firstmove++;
                    frm.txt.value=val;
                 }
                 swap(a+3,a);
             }
           }  
           var checker = true;
           for(var fg=0; fg<8; fg++)
           {
             if(jj[fg] == fg+1)
             {   }
             else
             {
               checker = false;
             }
           }  
    if(checker == true)
    {
      alert("You won.........");
      clearTimeout(ti);
    }
  }
  
}

else if(level==2)
{
   document.getElementById("lev2").checked=true;
   document.write("<table border=0 cellpadding=1>");
   document.write("<tr>");
   document.write('<td> <img name=i0 width=30px height=30px src="" onclick=moves1(0)></td>');
   document.write('<td> <img name=i1 width=30px height=30px src="" onclick=moves1(1)></td>');
   document.write('<td> <img name=i2 width=30px height=30px src="" onclick=moves1(2)></td>');
   document.write('<td> <img name=i3 width=30px height=30px src=""  onclick=moves1(3)></td>');
   document.write("</tr>");
   document.write("<tr>");
   document.write('<td> <img name=i4 width=30px height=30px src="" onclick=moves1(4)></td>');
   document.write('<td> <img name=i5 width=30px height=30px src="" onclick=moves1(5)></td>');
   document.write('<td> <img name=i6 width=30px height=30px src="" onclick=moves1(6)></td>');
   document.write('<td> <img name=i7 width=30px height=30px src="" onclick=moves1(7)></td>');
   document.write("</tr>");
   document.write("<tr>");
   document.write('<td> <img name=i8 width=30px height=30px src="" onclick=moves1(8)></td>');
   document.write('<td> <img name=i9 width=30px height=30px src="" onclick=moves1(9)></td>');
   document.write('<td> <img name=i10 width=30px height=30px src="" onclick=moves1(10)></td>');
   document.write('<td> <img name=i11 width=30px height=30px src="" onclick=moves1(11)></td>');
   document.write("</tr>");
   document.write("<tr>");
   document.write('<td> <img name=i12 width=30px height=30px src="" onclick=moves1(12)></td>');
   document.write('<td> <img name=i13 width=30px height=30px src="" onclick=moves1(13)></td>');
   document.write('<td> <img name=i14 width=30px height=30px src="" onclick=moves1(14)></td>');
   document.write('<td> <img name=i15 width=30px height=30px src="" onclick=moves1(15)></td>');
   document.write("</tr>");
   document.write("</table>");
    Array.prototype.inArray = function (value)
    {
      var i;
      for (i=0; i < this.length; i++) 
      {
        if (this[i] == value) 
        {
          return true;
         } 
      }   
       return false;
     };

     var xx;
     xx=16;
     var jj=new Array();
     while(xx>0)
     {
       var ff=Math.round(Math.random()*15);
       if(!jj.inArray(ff))
       {
          jj[jj.length]=ff;
          xx=xx-1;
       }  
     }
     for(var ffg=0;ffg<jj.length;ffg++)
     {
        var g=jj[ffg];
        var p=eval("document.images.i"+ffg);
        p.src="images1/"+g+".gif";
     }
     function swap(x,y)
     {
       var temp=jj[x];
       jj[x]=jj[y];
       jj[y]=temp;
       var p=eval("document.images.i"+x);
       p.src="images1/"+jj[x]+".gif";
       var p=eval("document.images.i"+y);
       p.src="images1/"+jj[y]+".gif";
     } 
     var firstmove=1;
     var t=0;
     function tim()
     {
       frm.txt1.value=t; 
       t=t+1;
       ti= setTimeout("tim()",1000);
     }
     function moves1(a)
     {
       var moved=false;
       if(a%4 != 0)
       {
         if(jj[a-1]==0)
         {
           moved=true;
           if(moved==true)
           {
             val=firstmove++;
             frm.txt.value=val;
           }
           swap(a-1,a);
         } 
       }  
       if((a+1)%4 !=0 && moved==false)
       {
         if(jj[a+1]==0)
         {
           moved=true;
           if(moved==true)
           {
             val=firstmove++;
             frm.txt.value=val;
           }
           swap(a+1,a);
         }   
       }
       if(a>3 && moved==false)
       {
         if(jj[a-4]==0)
         {
           moved=true;
           if(moved==true)
           {
              val=firstmove++;
              frm.txt.value=val;
           }
           swap(a-4,a);
          }
        }  
        if(a < 12 && moved==false)
        {
          if(jj[a+4]==0)
          {
             moved=true;
             if(moved==true)
             {
               val=firstmove++;
               frm.txt.value=val;
             }
             swap(a+4,a);
          }
        }  
       var checker=true;
       for(fg=0;fg<15;fg++)
       {
         if(jj[fg]==fg+1)
         { }
         else
         {
           checker=false;
         }
       }  
      if(checker==true)
      {
         alert("YOU WON...............");
         clearTimeout(ti);
      }  
   }
}
