// This file does not depend on jQuery by design. Keep it that way.
(function () {
  var dropdownTitle = '.header-dropdown-title';
  var dropdownActive = 'header-dropdown-active';
  var dropdownBody = '.header-dropdown-content';

  function parentElement(node) {
    if ('parentElement' in node) {
      return node.parentElement;
    }
    
    var parent = node.parentNode;
    while (parent) {
      if ('className' in parent) {
        return parent;
      } else {
        parent = parent.parentNode;
      }
    }
    return null;
  }
  
  function getWidth(element) {
    return Math.max(element.scrollWidth, element.offsetWidth, element.clientWidth)
  }

  function getHeight(element) {
    return Math.max(element.scrollHeight, element.offsetHeight, element.clientHeight);
  }

  function setClasses(element, obj) {
    var resolved = {};
    var parts, i, key;

    if (element.className !== '') {
      parts = element.className.split(' ');
      for (i = 0; i < parts.length; i++) {
        resolved[parts[i]] = true;
      }
    }

    for (key in obj) {
      if (obj.hasOwnProperty(key)) {
        resolved[key] = obj[key];
      }
    }

    parts = [];
    for (key in resolved) {
      if (resolved.hasOwnProperty(key) && resolved[key]) {
        parts.push(key);
      }
    }

    if (parts.length === 0) {
      element.className = '';
    } else {
      element.className = parts.join(' ');
    }
  }

  function setPosition(body, title, totalWidth, rtl) {
    var left;
    var offsetLeft = title.offsetLeft;
    var offsetTop = title.offsetTop;
    var width = getWidth(title);
    var height = getHeight(title);
    var right = offsetLeft + width;
    var bodyWidth = getWidth(body);

    if (rtl) {
      if ((offsetLeft + width) < bodyWidth) {
        if ((offsetLeft + bodyWidth) < totalWidth) {
          left = offsetLeft;
        } else {
          left = totalWidth - bodyWidth;
        }
      } else {
        left = right - bodyWidth;
      }
    } else {
      if ((offsetLeft + bodyWidth) > totalWidth) {
        if (bodyWidth > right) {
          left = Math.max(0, totalWidth - bodyWidth);
        } else {
          left = right - bodyWidth;
        }
      } else {
        left = offsetLeft;
      }
    }

    body.style.left = left + 'px';
    body.style.top = (offsetTop + height) + 'px';
  }

  function computeStyle(node) {
    return window.getComputedStyle ? window.getComputedStyle(node, null) : node.currentStyle;
  }

  function updateDropdowns() {
    var totalWidth = document.body.clientWidth;
    var nodeList = document.querySelectorAll(dropdownBody);
    var i;
    var body;

    for (i = 0; i < nodeList.length; i++) {
      body = nodeList[i];
      var title = parentElement(body).querySelector(dropdownTitle);
      var dir = computeStyle(title).direction;

      if (body.style.display === 'block') {
        if (!body.style.width) {
          body.style.width = getWidth(body) + 'px';
        }
        setClasses(title, {'header-dropdown-active': true});
        setPosition(body, title, totalWidth, dir === "rtl");
      } else {
        setClasses(title, {'header-dropdown-active': false});
        body.style.width = '';
      }
    }
  }

  function bind(f, that) {
    return function () {
      return f.apply(that, arguments);
    };
  }

  function onEvent(targets, type, f) {
    var i, node;
    for (i = 0; i < targets.length; i++) {
      node = targets[i];
      if (node.addEventListener) {
        node.addEventListener(type, bind(f, node), false);
      } else if (node.attachEvent) {
        node.attachEvent('on' + type, bind(f, node));
      }
    }
  }

  function hasClass(element, className) {
    if (element.className === '') {
      return false;
    }
    var parts = element.className.split(' ');
    var i;
    for (i = 0; i < parts.length; i++) {
      if (parts[i] === className) {
        return true;
      }
    }
    return false;
  }

  function hasParentWithClass(element, className) {
    var ptr = element;
    while (ptr) {
      if (hasClass(ptr, className)) {
        return true;
      }
      ptr = parentElement(ptr);
    }
  }

  onEvent(document.querySelectorAll(dropdownTitle), 'click', function () {
    var title = parentElement(this).querySelector(dropdownTitle);
    var self = parentElement(this).querySelector(dropdownBody);
    var visible = self.style.display === 'block';

    var i, nodes;
    nodes = document.querySelectorAll(dropdownBody);
    for (i = 0; i < nodes.length; i++) {
      nodes[i].style.display = 'none';
    }

    if (!visible) {
      self.style.display = 'block';
    }
    updateDropdowns();
  });
  onEvent([document], 'click', function (e) {
    if (!hasParentWithClass(e.target || e.srcElement, 'header-dropdown')) {

      var i, nodes;
      nodes = document.querySelectorAll(dropdownBody);
      for (i = 0; i < nodes.length; i++) {
        nodes[i].style.display = 'none';
      }

      updateDropdowns();
    }
  });
  onEvent([window], 'resize', updateDropdowns);

  function doSearch(e) {
		var textBox = document.getElementById('header-search');
		if (textBox.value === textBox.defaultValue) {
			textBox.value = '';
		}
    var text = encodeURIComponent(textBox.value);
    var url;

    switch (document.getElementById('header-search-type').value) {
      case 'parts':
        url = format(__headerData.partSearchUrl, text);
        break;
      case 'content':
        url = format(__headerData.contentSearchUrl, text);
        break;
    }

    location.href = url;
    if (e.preventDefault) {
			e.preventDefault(true);
		} else {
			e.returnValue = false;
		}
  }

  onEvent([document.getElementById('header-search-type')], 'change', function (e) {
		var name;
    switch (document.getElementById('header-search-type').value) {
      case 'parts':
		name = __headerData.partSearchName;
        break;
      case 'content':
		name = __headerData.contentSearchName;
        break;
    }
		document.getElementById('header-search').setAttribute('name', name);
  });
  onEvent([document.getElementById('header-search-button')], 'click', doSearch);
  onEvent([document.getElementById('header-search')], 'keydown', function (e) {
    if (e.keyCode === 13) {
      doSearch(e);
    }
  });

  function Tokenizer() {
    this.patterns = [];
  }

  Tokenizer.prototype.add = function add(name, pattern) {
    this.patterns.push({name: name, pattern: new RegExp(pattern, 'g')});
  };

  Tokenizer.prototype.parse = function (input) {
    var res = [];
    var ptr = 0;
    var i, pattern, match, matched;
    while (ptr < input.length) {
      matched = false;
      for (i = 0; i < this.patterns.length; i++) {
        pattern = this.patterns[i];
        pattern.pattern.lastIndex = ptr;
        match = pattern.pattern.exec(input);
        if (match && match.index === ptr) {
          matched = true;
          res.push({name: pattern.name, groups: match, text: match[0]});
          ptr = ptr + match[0].length;
          break;
        }
      }
      if (!matched) {
        throw new Error();
      }
    }
    return res;
  };

  var semiRichGrammar = new Tokenizer();
  semiRichGrammar.add('entity', '&([\\w\\d#-]+);');
  semiRichGrammar.add('{', '\\{\\{');
  semiRichGrammar.add('placeholder', '\\{(\\d+)\\}');
  semiRichGrammar.add('literal', '.[^{&]*');

  function formatSemiRich(pattern) {
    var tokens = semiRichGrammar.parse(pattern);
    var i, token, ent;

    var res = [];
    for (i = 0; i < tokens.length; i++) {
      token = tokens[i];
      switch (token.name) {
        case 'entity':
          ent = __headerData.entities[token.groups[1]];
          if (ent) {
            res.push(ent);
          } else {
            res.push(token.text);
          }
          break;

        case '{':
          res.push('{');
          break;

        case 'placeholder':
          res.push(htmlEscape(arguments[parseInt(token.groups[1]) + 1]));
          break;

        case 'literal':
          res.push(htmlEscape(token.text));
          break;
      }
    }
    return res.join('');
  }

  var entityTextGrammar = new Tokenizer();
  entityTextGrammar.add('entity', '&([\\w\\d#-]+);');
  entityTextGrammar.add('literal', '.[^&]*');

  function formatEntityText(text) {
    var tokens = entityTextGrammar.parse(text);
    var i, token, ent;

    var res = [];
    for (i = 0; i < tokens.length; i++) {
      token = tokens[i];
      switch (token.name) {
        case 'entity':
          res.push(token.text);
          break;

        case 'literal':
          res.push(htmlEscape(token.text));
          break;
      }
    }
    return res.join('');
  }

  var formatGrammar = new Tokenizer();
  formatGrammar.add('{', '\\{\\{');
  formatGrammar.add('placeholder', '\\{(\\d+)\\}');
  formatGrammar.add('literal', '[^{]+');

  function format(pattern) {
    var tokens = formatGrammar.parse(pattern);
    var i, token, ent;

    var res = [];
    for (i = 0; i < tokens.length; i++) {
      token = tokens[i];
      switch (token.name) {
        case '{':
          res.push('{');
          break;

        case 'placeholder':
          res.push(arguments[parseInt(token.groups[1]) + 1]);
          break;

        case 'literal':
          res.push(token.text);
          break;
      }
    }
    return res.join('');
  }

  function htmlEscape(str) {
    return str.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;').replace(/"/g, '&quot;');
  }

  function updateTextDirection(e) {
    var target = e.target || e.srcElement;
    if (computeStyle(parentElement(target)).direction === 'ltr') {
      target.style.direction = 'ltr';
      return;
    }
    setTimeout(function () {
      var value = target.value;
      var rtl = false;
      var i, char;
      for (i = 0; i < value.length; i++) {
        char = value.charCodeAt(i);
        if (char >= 1488 && char <= 1514) {
          rtl = true;
        }
      }
      target.style.direction = rtl ? 'rtl' : 'ltr';
    }, 0);
  }

  (function () {
    var targets = document.querySelectorAll('.dkdirchanger');
    onEvent(targets, 'change', updateTextDirection);
    onEvent(targets, 'paste', updateTextDirection);
    onEvent(targets, 'keydown', updateTextDirection);
    onEvent(targets, 'keyup', updateTextDirection);
    var i;
    for (i = 0; i < targets.length; i++) {
      updateTextDirection({target: targets[i]});
    }
  }());

  function getCookieValue(key) {
    // From MDN
    return decodeURIComponent(document.cookie.replace(new RegExp("(?:(?:^|.*;)\\s*" + encodeURIComponent(key).replace(/[\-\.\+\*]/g, "\\$&") + "\\s*\\=\\s*([^;]*).*$)|^.*$"), "$1")) || null;
  }

  function getQueryStringValue(key) {
		var kvs = window.location.search.substring(1).split('&');
		var i, parts;
		for (i = 0; i < kvs.length; i++) {
			parts = kvs[i].split('=');
			if (parts[0] === key) {
				return parts[1];
			}
		}
		return undefined;
	}
	
  (function () {
    var cur = getCookieValue('cur') || getQueryStringValue('curr');
		var element = document.querySelector('.header-currency');
    if (cur && element) {
      element.textContent = cur;
    }
  }());

  function setPersonalization(dataStr) {
    var data = JSON.parse(dataStr);
    var headerCart = document.getElementById('header-cart');
    var myDK = document.getElementById('header-login');
    if (myDK) {
      setMyDigikey(document.getElementById('header-login-title'), myDK.querySelector(dropdownBody), data['DisplayName']);
    }
    if (headerCart) {
      setCart(headerCart.querySelector('.header-dropdown-title'), headerCart.querySelector(dropdownBody), data);
    }
  }

  function formatProperty(prop) {
    return prop['Label'] + ' ' + prop['Value'];
  }

  function setCart(title, body, data) {
    var count = data['Count'];
    var viewCart = body.querySelector('.header-view-cart');
    var effective = data['Details'].length;
    var i, detail, div, el, imgSrc;
    title.innerHTML = formatSemiRich(__headerData.cartTitle, count);
    viewCart.innerHTML = formatSemiRich(__headerData.viewCart, count);

    for (i = 0; i < effective; i++) {
      detail = data['Details'][i];

      div = document.createElement('div');
      div.className = 'header-cart-detail';
      el = document.createElement('img');
			imgSrc = detail['Image'];
			if (!imgSrc) {
				imgSrc = __headerData.noImage;
			}
      el.src = imgSrc;
			if (imgSrc) {
				div.appendChild(el);
			}
      el = document.createElement('p');
      el.className = 'header-cart-pn';
      el.innerHTML = formatProperty(detail['PartNumber']);
      div.appendChild(el);
      el = document.createElement('p');
      el.className = 'header-cart-ref';
      el.innerHTML = formatEntityText(detail['CustomerReference']['Value']);
      div.appendChild(el);
      el = document.createElement('p');
      el.className = 'header-cart-quantity';
      el.textContent = formatProperty(detail['Quantity']);
      div.appendChild(el);
      el = document.createElement('p');
      el.className = 'header-cart-ref';
      el.textContent = detail['Price']['Value'];
      div.appendChild(el);
      body.appendChild(div);

      if (i !== (effective - 1)) {
        el = document.createElement('hr');
        el.className = 'header-dropdown-sep';
        body.appendChild(el);
      }
    }

    el = document.createElement('p');
    el.id = 'header-cart-disclaimer';
    el.innerHTML = data['Disclaimer'];
    body.appendChild(el);
    body.appendChild(viewCart);
  }

  function createButton(text, href) {
    var a = document.createElement('a');
    a.className = 'header-button';
    a.href = href;
    a.innerHTML = text;
    return a;
  }

  function setMyDigikey(title, body, name) {
    var titleParts = title.querySelectorAll('p');
    if (name === '') {
      return;
    }

    titleParts[0].innerHTML = formatSemiRich(__headerData.userLine1, name);
    titleParts[1].innerHTML = formatSemiRich(__headerData.userLine2, name);

    body.innerHTML = '';
    var link, i;
    for (i = 0; i < __headerData.links.length; i++) {
      link = __headerData.links[i];
      body.appendChild(createButton(formatSemiRich(link.title), link.link));
    }
  }

  function getPersonalization() {
    var request = new XMLHttpRequest();
    var site = __headerData.site;
    var lang = __headerData.lang;
    var cur = getCookieValue('cur') || __headerData.cur;
		var url = '/classic/headerinfo.ashx?site=' + site + '&lang=' + lang + '&cur=' + cur;
		if (window.location.host.match(/^local/)) {
			url = url.replace('classic', 'localordering');
		}
		request.open('GET', url, true);

    request.onreadystatechange = function () {
      if (this.readyState === 4) {
        if (this.status >= 200 && this.status < 400) {
          setPersonalization(this.responseText);
        }
      }
    };

    request.send();
    request = null;
  }

  getPersonalization();
}());
