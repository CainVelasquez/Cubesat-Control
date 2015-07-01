// starts the currency gathering process
CurrencySetter.findCurrency = function () {
  CurrencySetter.checkQS();
  CurrencySetter.checkCookie();
  CurrencySetter.doDefault();
}

// checks the query string for currency specifications
CurrencySetter.checkQS = function () {
  //alert(CurrencySetter.country);
  var queryString = window.location.search.substring(1);
  var queryStringArray = queryString.split("&");
  for (i = 0; i < queryStringArray.length; i++) {
    var nameValuePair = queryStringArray[i].split("=");
    CurrencySetter.qsParams[nameValuePair[0]] = nameValuePair[1];
  }

  if (CurrencySetter.qsParams.curr) {
    CurrencySetter.setCurrency(CurrencySetter.qsParams.curr);
  }
}

// checks the cookie for currency information if currency not set yet
CurrencySetter.checkCookie = function () {
  if (CurrencySetter.currency == "") {
    var cookie = CurrencySetter.getCookie("cur");
    if (cookie != "" && CurrencySetter.isValid(cookie)) {
      CurrencySetter.setCurrency(cookie);
    }
  }
}

// gets the default currency if currency is not set yet
CurrencySetter.doDefault = function () {
  if (CurrencySetter.currency == "") {
    CurrencySetter.setCurrency(CurrencySetter.validCurrencies[CurrencySetter.country][0]);
  }
}

// checks if the given currency is valid for the given country
CurrencySetter.isValid = function (currency) {
  var result = false;
  var currencies = CurrencySetter.validCurrencies[CurrencySetter.country];

  currency = currency.toUpperCase();
  for (var i = 0; i < currencies.length; i++) {
    if (currency == currencies[i]) {
      result = true;
    }
  }
  //alert(result);
  return result;
}

// sets a cookie with the given name, value and expiration
CurrencySetter.setCookie = function (c_name, value, expireDays) {
  var cookieExpiration = "";
  var path = ";path=/";  // makes cookie available to any path
  var domain = document.domain;
  if (domain.indexOf(".") != -1) {  // places it on the main domain
    domain = domain.substr(domain.indexOf(".") + 1);
  }
  //alert("Domain:" + domain);

  if (expireDays != null) { // Sets expires date
    var exdate = new Date();
    exdate.setDate(exdate.getDate() + expireDays);
    cookieExpiration = ";expires=" + exdate.toGMTString();
  }

  var nameValue = c_name + "=" + escape(value);
  var domain = ";domain=" + domain;

  document.cookie = nameValue + cookieExpiration + path + domain;
  //alert("Cookie Info:" + nameValue + cookieExpiration + path + domain);
  // alert("cookie set:" + CurrencySetter.getCookie("cur"));
}

// gets a cookie with the given name
CurrencySetter.getCookie = function (c_name) {
  if (document.cookie.length > 0) {
    c_start = document.cookie.indexOf(c_name + "=");
    if (c_start != -1) {
      c_start = c_start + c_name.length + 1;
      c_end = document.cookie.indexOf(";", c_start);
      if (c_end == -1) {
        c_end = document.cookie.length;
      }
      return unescape(document.cookie.substring(c_start, c_end));
    }
  }
  return "";
}

// Sets the currency to the given value if valid
CurrencySetter.setCurrency = function (currency) {
  currency = currency.toUpperCase();
  if (CurrencySetter.prompt) {
    CurrencySetter.prompt.dialog('close');
  }
  if (CurrencySetter.isValid(currency)) {
    CurrencySetter.currency = currency;
    //alert("Setting Cookie to: " + currency);
    CurrencySetter.setCookie("cur", currency, 30);
    CurrencySetter.setCookie("SiteForCur", CurrencySetter.country, 30);
    //alert("Cookie Value:" + CurrencySetter.getCookie("cur"));
    CurrencySetter.redraw();
    if (CurrencySetter.isLoad) {
      CurrencySetter.isLoad = false;
    } else {
      CurrencySetter.refresh();
    }
  } else {
    //alert("Currency Not Valid");
  }
}

// will toggle the currency parameter in links
CurrencySetter.toggleLinks = function () {
  if (CurrencySetter.currency != "") {
    $("a").each(function () {
      var link = $(this).attr("href");
      if (link) {
        if (link.match(/[&?]curr/)) {
          link = link.replace(/([&?])curr=[^&?+]*([&?+]?.*)$/gi, "$1curr=" + CurrencySetter.currency + "$2");
          $(this).attr("href", link);
        }
      }
    });
  }
}

// Redraws the page without a refresh
CurrencySetter.redraw = function () {
  CurrencySetter.toggleCurrency();
  if (CurrencySetter.toggleLinks) {
    CurrencySetter.toggleLinks();
  }
}

// Function to overload if refresh of page need on currency change
CurrencySetter.refresh = function () { }

// Loads up the Prompt for switching currencies
CurrencySetter.currencyPrompt = function () {
  // alert(CurrencySetter.promptPage);
  $.get(CurrencySetter.promptPage, function (data) {
    var contents = $(data);
    var titleText = contents.find("#title").detach().text();
    if (titleText == "") { // just in case the old way of <title> is still being used
      titleText = contents.find("title").text();
    }
    var dialogWidth = contents.css("width").replace(/px/gi, "");
    // alert(dialogWidth);
    if (!dialogWidth) {
      dialogWidth = 500;
    } else {
      dialogWidth = parseInt(dialogWidth);
    }
    CurrencySetter.prompt = contents.dialog({
      height: 425,
      width: dialogWidth,
      title: titleText,
      modal: true
    });
  });
}

CurrencySetter.toggleCurrency = function () {
  var currencies = $(".currency");
  currencies.hide();
  currencies.filter("." + CurrencySetter.currency).show();
}

// Starts the currency setting when ready
$(window).load(function () {
  CurrencySetter.findCurrency();
  CurrencySetter.toggleCurrency();
});
