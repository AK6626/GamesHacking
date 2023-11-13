var q = document.getElementById('qsearch');
q.addEventListener('focus', (event) => {
    if (typeof games === "undefined") {
        fetch('/api/' + document.getElementsByTagName('html')[0].getAttribute('lang') + '/games')
            .then(response => response.json())
            .then(data => {
                games = data;
            });
    }
});

q.addEventListener('keyup', (event) => {
    var query = event.target.value.toLowerCase();
    var results = document.getElementById('qresults');
    var maxResults = 12;
    var i, j;
    var opts = [];

    results.innerHTML = '';
    if (query.length < 2) {
        return;
    }
    for (i = 0; i < games.length; i++) {
        for (j = 0; j < games[i].search.length; j++) {
            let f = games[i].search[j].indexOf(query);
            if (f > -1) {
                let text = document.createTextNode(games[i].label);
                let link = document.createElement("a");
                link.setAttribute('href', games[i].url);
                link.appendChild(text);
                let li = document.createElement("li");
                li.onclick = function() {
                    this.children[0].click();
                };
                li.appendChild(link);
                if (f == 0) {
                    maxResults--;
                    results.appendChild(li);
                } else {
                    opts.push(li);
                }
                if (maxResults == 0) {
                    return;
                }
                break;
            }
        }
    }
    for (i = 0; i < opts.length; i++) {
        maxResults--;
        results.appendChild(opts[i]);
        if (maxResults == 0) {
            return;
        }
    }
});

document.getElementById('themePicker').addEventListener('click', (event) => {
    var theme = document.getElementsByTagName('body')[0].classList[0];
    if (theme == 'dark') {
        document.getElementsByTagName('body')[0].classList.remove('dark');
        localStorage.setItem('theme', 'light');
        // document.cookie = "theme=light; expires=Fri, 31 Dec 9999 23:59:59 GMT; path=/; secure; samesite=strict";
    } else {
        document.getElementsByTagName('body')[0].classList.add('dark');
        localStorage.setItem('theme', 'dark');
        // document.cookie = "theme=dark; expires=Fri, 31 Dec 9999 23:59:59 GMT; path=/; secure; samesite=strict";
    }
});

var header_slider = null;
var header_x = 0;
var header_dx = 0;
var header_w = 0;
var header_dw = 0;
var header_moving = false;
var header_def_el = null;

function header_m_light(el) {
    if (el == null) return;
    if (header_def_el == null) {
        header_def_el = el;
    }
    if (header_slider == null) {
        header_slider = document.getElementById('header_slider');
    }
    header_dx = el.offsetLeft - 2;
    header_dw = el.offsetWidth + 4;
    header_slider.style.height = el.offsetHeight + 8 + 'px';
    if (!header_moving) header_move_slider();
}

function header_move_slider() {
    if (header_x != header_dx) {
        header_moving = true;
        var d = (header_dx > header_x) ? 1 : -1;
        var mx = Math.round((header_dx - header_x) / 4);
        if (mx == 0) mx = d;
        header_x += mx;
        header_slider.style.marginLeft = header_x + 'px';

        if (header_dw != header_w) {
            var d = (header_dw > header_w) ? 1 : -1;
            var mw = Math.round((header_dw - header_w) / 4);
            if (mw == 0) mw = d;
            header_w += mw;
            header_slider.style.width = header_w + 'px';
        }

        setTimeout('header_move_slider()', 30);
    } else {
        if (header_w != header_dw) {
            header_w = header_dw;
            header_slider.style.width = header_w + 'px';
        }
        header_moving = false;
    }
}
