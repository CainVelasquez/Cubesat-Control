//tealium universal tag - utag.sender.1134 ut4.0.201502092028, Copyright 2015 Tealium.com Inc. All Rights Reserved.
//~~tv:1134.20130212
//~~tc: Initial version.
try{
(function(id,loader,u){
  try{u=utag.o[loader].sender[id]={}}catch(e){u=utag.sender[id]};
  u.ev={'view':1,'link':1};
  u.qsp_delim=";";
  u.kvp_delim=":";
  u.advid="905";
  u.gid="3315";
  u.pid="394936";
  u.base_url="//js.dmtry.com/channel.js#";
  u.map={"meta.wt.z_supplier_id":"cus.sid"};
  u.extend=[function(a,b){ try{ if(typeof b['meta.wt.z_supplier_id']=='undefined'){b['meta.wt.z_supplier_id']='0'} } catch(e){ utag.DB(e) }  }];

  u.send=function(a,b){
    if(u.ev[a]||typeof u.ev.all!="undefined"){
      //utag.DB("send:48");
      for(c=0;c<u.extend.length;c++){try{d=u.extend[c](a,b);if(d==false)return}catch(e){}};
      var c,d,e,f,g;
      c=[];g=[];
      for(d in utag.loader.GV(u.map)){if(typeof b[d]!="undefined"&&b[d]!=""){e=u.map[d].split(",");for(f=0;f<e.length;f++){
       //original call without sid if(e[f].indexOf("cus.")==0){
	//New Call for Adometry Config
	if(e[f].indexOf("cus.")==0 || e[f].indexOf("sid")==0) 
	{
          g.push(e[f]+u.kvp_delim+encodeURIComponent(b[d]));
        }
	else
	{
          u[e[f]]=encodeURIComponent(b[d]);
        }
      }}}
      c.push("gid"+u.kvp_delim+u.gid,"advid"+u.kvp_delim+u.advid,"pid"+u.kvp_delim+u.pid);
      c=c.concat(g);
      u.s=document.getElementsByTagName("script")[0];u.scr=document.createElement("script");u.scr.type="text/javascript";u.scr.src=u.base_url+c.join(u.qsp_delim);
      u.s.parentNode.insertBefore(u.scr,u.s);
      //utag.DB("send:48:COMPLETE");
    }
  }
  try{utag.o[loader].loader.LOAD(id)}catch(e){utag.loader.LOAD(id)}
})('48','digikey.main');
}catch(e){}
//end tealium universal tag
//~~tv:1134.20130212

