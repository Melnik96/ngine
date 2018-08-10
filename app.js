const cheerio = require('cheerio')
const request = require('request')
const cloudscraper = require('cloudscraper')
const fs = require('fs')

var tough = require('tough-cookie')

//jar: cloudkicker.cookieJar,



function save_cookies(proxy_id, data) {
    fs.writeFile("./cookies-"+proxy_id, data, function(err) {
        if(err) {
            return console.log('save_cookies err', err);
        }

        console.log("save_cookies ok!");
    })
}

function restore_cookies(proxy_id, cb) {
    fs.readFile("./cookies-"+proxy_id, function(err, data) {
        if (err) {
            cb(true, null)
            return
        }

        cb(false, data)

        console.log("restore_cookies ok!");
    })
}



function clients(proxies) {
    this.cur_index = 0
    this.ready_count = 0
    this.intences = []

    this.next = function() {
        let ret = this.intences[this.cur_index]

        this.cur_index++

        if(this.cur_index == this.intences.length) {
            this.cur_index = 0
        }

        return ret
    }

    this.each = function(init_cb, done_cb) {
        for(let i = 0; i < proxies.length; i++){
            init_cb(proxies[i], (jar, csrf) => {
                this.intences.push({ proxy: proxies[i], jar: jar, csrf: csrf })
                this.ready_count++

                if(this.ready_count == proxies.length) {
                    console.log('init done', this.intences)
                    done_cb()
                }
            })
        }
    }
}



let cls = new clients([
    //my first project
    'http://35.236.18.187:3128',
    'http://35.236.68.94:3128',
    'http://35.235.121.154:3128',
    'http://35.235.105.209:3128',
    'http://35.236.121.18:3128',
    'http://35.235.81.1:3128',
    'http://35.236.71.98:3128',
    'http://35.235.126.146:3128',

    //proxy-1
    'http://35.235.93.91:3128',
    'http://35.236.106.9:3128',
    'http://35.236.47.235:3128',
    'http://35.236.74.9:3128',
    'http://35.235.95.214:3128',
    'http://35.236.114.242:3128',
    'http://35.235.97.236:3128',
    'http://35.236.25.61:3128',

    //proxy-2
    'http://35.235.71.105:3128',
    'http://35.235.117.74:3128',
    'http://35.236.51.48:3128',
    'http://35.235.98.202:3128',
    'http://35.236.40.58:3128',
    'http://35.236.69.225:3128',
    'http://35.236.91.107:3128',
    'http://35.236.109.181:3128',
    'http://35.235.72.0:3128',
    'http://35.236.51.245:3128',
    'http://35.236.20.55:3128',
    'http://35.236.66.95:3128',
    'http://35.236.108.110:3128',
    'http://35.236.117.216:3128',
    'http://35.236.78.195:3128',
    'http://35.236.123.62:3128',
    'http://35.236.72.206:3128',
    'http://35.236.112.195:3128',
    'http://35.236.106.194:3128',
    'http://35.235.102.196:3128',
    'http://35.235.108.84:3128',
    'http://35.236.69.233:3128',
    'http://35.236.55.112:3128',
    'http://35.236.62.123:3128',

    //proxy-3
    'http://35.236.106.252:3128',
    'http://35.236.107.182:3128',
    'http://35.235.73.2:3128',
    'http://35.236.34.58:3128',
    'http://35.235.121.12:3128',
    'http://35.236.120.126:3128',
    'http://35.236.56.88:3128',
    'http://35.236.86.76:3128',
    'http://35.236.33.40:3128',
    'http://35.236.52.62:3128',
    'http://35.236.106.191:3128',
    'http://35.235.93.237:3128',
    'http://35.235.84.15:3128',
    'http://35.236.111.237:3128',
    'http://35.236.19.24:3128',
    'http://35.236.41.244:3128',
    'http://35.236.98.11:3128',
    'http://35.236.23.246:3128',
    'http://35.236.12.71:3128',
    'http://35.235.108.64:3128',
    'http://35.236.118.107:3128',
    'http://35.236.104.122:3128',
    'http://35.236.56.160:3128',
    'http://35.236.33.240:3128',
    'http://35.236.0.78:3128',
    'http://35.235.70.204:3128',
    'http://35.236.4.175:3128',
    'http://35.235.97.110:3128',
    'http://35.235.115.248:3128',
    'http://35.235.69.170:3128',
    'http://35.235.106.17:3128',
    'http://35.236.88.192:3128',
    'http://35.236.5.67:3128',
    'http://35.236.32.164:3128',
    'http://35.235.112.159:3128',
    'http://35.235.125.180:3128',
    'http://35.236.10.119:3128',
    'http://35.236.63.15:3128',
    'http://35.235.73.239:3128',
    'http://35.236.7.61:3128',
    'http://35.236.84.190:3128',
    'http://35.236.30.169:3128',
    'http://35.236.78.15:3128',
    'http://35.235.125.134:3128',
    'http://35.236.36.56:3128',
    'http://35.236.66.215:3128',
    'http://35.235.92.255:3128',
    'http://35.236.78.73:3128',
    'http://35.235.108.32:3128',
    'http://35.236.80.246:3128',
    'http://35.235.105.122:3128',
    'http://35.235.126.62:3128',
    'http://35.236.73.181:3128',
    'http://35.235.118.116:3128',
    'http://35.235.75.217:3128',
    'http://35.235.70.17:3128',
    'http://35.236.63.65:3128',
    'http://35.236.42.32:3128',
    'http://35.235.104.239:3128',
    'http://35.236.116.71:3128',
    'http://35.235.96.84:3128',
    'http://35.236.64.136:3128',
    'http://35.236.46.148:3128',
    'http://35.235.85.79:3128',

    //proxy-4
    'http://35.235.117.179:3128',
    'http://35.235.112.178:3128',
    'http://35.236.46.216:3128',
    'http://35.236.116.66:3128',
    'http://35.236.10.131:3128',
    'http://35.236.126.60:3128',
    'http://35.236.106.223:3128',
    'http://35.236.114.196:3128',
    'http://35.235.111.83:3128',
    'http://35.236.20.219:3128',
    'http://35.236.3.149:3128',
    'http://35.236.111.108:3128',
    'http://35.235.79.137:3128',
    'http://35.235.80.242:3128',
    'http://35.235.69.120:3128',
    'http://35.236.6.173:3128',
    'http://35.236.77.14:3128',
    'http://35.236.86.38:3128',
    'http://35.236.63.40:3128',
    'http://35.236.69.170:3128',
    'http://35.236.12.56:3128',
    'http://35.235.87.3:3128',
    'http://35.236.64.149:3128',
    'http://35.236.1.89:3128',
    'http://35.235.115.52:3128',
    'http://35.235.108.191:3128',
    'http://35.236.15.145:3128',
    'http://35.236.104.226:3128',
    'http://35.236.115.245:3128',
    'http://35.235.103.41:3128',
    'http://35.236.110.236:3128',
    'http://35.236.41.37:3128',
    'http://35.236.31.200:3128',
    'http://35.236.72.211:3128',
    'http://35.236.26.107:3128',
    'http://35.236.3.207:3128',
    'http://35.235.92.185:3128',
    'http://35.236.101.14:3128',
    'http://35.236.89.136:3128',
    'http://35.236.49.157:3128',
    'http://35.235.88.177:3128',
    'http://35.236.41.36:3128',
    'http://35.235.73.88:3128',
    'http://35.236.32.172:3128',
    'http://35.235.75.49:3128',
    'http://35.236.22.25:3128',
    'http://35.235.69.99:3128',
    'http://35.235.89.187:3128',
    'http://35.235.64.31:3128',
    'http://35.236.17.185:3128',
    'http://35.236.43.181:3128',
    'http://35.235.121.26:3128',
    'http://35.236.98.165:3128',
    'http://35.236.93.155:3128',
    'http://35.236.63.117:3128',
    'http://35.235.79.22:3128',
    'http://35.235.79.95:3128',
    'http://35.236.9.222:3128',
    'http://35.236.38.221:3128',
    'http://35.236.86.31:3128',
    'http://35.236.97.164:3128',
    'http://35.236.106.48:3128',
    'http://35.236.45.69:3128',
    'http://35.235.102.46:3128',
])

cls.each((proxy, res_jar) => {
    let j = request.jar()
    console.log(j)


    restore_cookies(proxy.replace('http://', ''), (err, data) => {
        if(err) {
            setup_cookies()
        } else {
            j._jar = tough.CookieJar.fromJSON(JSON.parse(data))
            const csrf = j._jar.store.idx['opskins.com']['/'].opskins_csrf_token.toString().slice(19, 52)
            res_jar(j, csrf)
            console.log(j)
        }
    })


    function setup_cookies() {
        j.setCookie(request.cookie('n_lang=en-US'), 'http://opskins.com')
        j.setCookie(request.cookie('timezone_offset=3%2C1'), 'http://opskins.com')
        j.setCookie(request.cookie('eu_cookie_accepted=auto'), 'http://opskins.com')
        j.setCookie(request.cookie('opskins_hasLoggedIn=true'), 'http://opskins.com')
        j.setCookie(request.cookie('sale-graph-type=1'), 'http://opskins.com')
        j.setCookie(request.cookie('selectedApp=1912_1'), 'http://opskins.com')
        j.setCookie(request.cookie('opskins_login_token=MGL4nHfRWJ49dbgQcKnDQ8tgeRe08wCq'), 'http://opskins.com')
        j.setCookie(request.cookie('machine_auth[5329937]=nzC0bxGqJ0SfD8GeDAMZp638aK706qz3'), 'http://opskins.com')
        j.setCookie(request.cookie('PHPSESSID=ir5jipfomclbgufhi7lmsn97k4'), 'http://opskins.com')

        cloudscraper.request({
            method: 'GET',
            proxy:proxy,
            url: "https://opskins.com/?loc=shop_browse&app=1912_1",
            jar: j
        }, (error, response, body) => {
            //console.log(error, response, body)

            cloudscraper.request({
                method: 'GET',
                proxy:proxy,
                url: "https://opskins.com/ajax/browse_scroll.php?page=1&appId=1912&contextId=1",
                jar: j
            }, (error, response, body) => {
                function reppp() {
                    cloudscraper.request({
                        method: 'GET',
                        proxy:proxy,
                        url: 'https://opskins.com/?loc=shop_search&sort=lh&app=1912_1&search_item="Skeleton%20Key"&search_internal=1',
                        jar: j
                    }, (error, response, body) => {
                        //console.log(error, response, body)
                        //console.log(j)

                            const csrf = j._jar.store.idx['opskins.com']['/'].opskins_csrf_token.toString().slice(19, 52)
                            const cf_clearance = j._jar.store.idx['opskins.com']['/'].cf_clearance

                            if(cf_clearance) {
                                console.log(JSON.stringify(j._jar.serializeSync()))
                                save_cookies(proxy.replace('http://', ''), JSON.stringify(j._jar.serializeSync()))

                                res_jar(j, csrf)
                            } else {
                                console.log('reppp()')
                                reppp()
                            }

                    })
                }
                reppp()
            })

            //reload_items(headers)
        })
    }
}, () => {
    reload_prices(cls.next(), () => {
        setInterval(() => { reload_prices(cls.next(), () => {}) }, 10*60*1000)

        setInterval(() => { reload_items(cls.next()) }, 150)
    })
})




    function load_prices($, csrf, j, proxy) {
        let fi = $('.featured-item')
        //console.log(csrf, proxy)
        if(fi.length == 0) {
            console.log('fi.size() == 0', proxy)
            return
        } else {
            //console.log('fi.size() OK')
        }

        fi.each(function(index, value) {
            const _index = index
            const _value = value = cheerio(value)
            const price = value.attr('data-amount')/100
            const market_name = value.find('.market-name.market-link').text().replace('\n', '').replace('\n', '')
            let market_hash_name = market_name

            let exterior = null

            if(market_name.indexOf('Key') == -1) {
                exterior = value.find('.text-muted').text()

                if(exterior.indexOf('Factory New') != -1) {
                    exterior = 'fn'
                    market_hash_name = market_name+' (Factory New)'
                } else if(exterior.indexOf('Minimal Wear') != -1) {
                    exterior = 'mw'
                    market_hash_name = market_name+' (Minimal Wear)'
                } else if(exterior.indexOf('Well-Worn') != -1) {
                    exterior = 'ww'
                    market_hash_name = market_name+' (Well-Worn)'
                } else if(exterior.indexOf('Field-Tested') != -1) {
                    exterior = 'ft'
                    market_hash_name = market_name+' (Field-Tested)'
                } else if(exterior.indexOf('Battle-Scarred') != -1) {
                    exterior = 'bs'
                    market_hash_name = market_name+' (Battle-Scarred)'
                }
            }

            if(blacklist[market_hash_name] != null && price > blacklist[market_hash_name]) {
                return;
            }

            const opdb_item = op_lowest_prices[market_hash_name]
            //console.log(opdb_item)

            if(opdb_item != null) {
                _opdb_item_price = opdb_item.price/100

                if(price >= 10 && price > _opdb_item_price*0.85) {
                    return
                }

                if(opdb_item.quantity > 30) {
                    if(price+0.03 < _opdb_item_price && price < _opdb_item_price*0.95) {
                        console.log('hyper fast buy '+price, _opdb_item_price, market_hash_name)
                        buy_item(value.find('.btn.btn-success').attr('data-id'), value.attr('data-amount'), 'shop_search', 1, csrf)
                    }
                } else if(opdb_item.quantity > 5) {
                    if(price+0.03 < _opdb_item_price && price < _opdb_item_price*0.85) {
                        console.log('hyper fast buy q5 '+price, _opdb_item_price, market_hash_name)
                        buy_item(value.find('.btn.btn-success').attr('data-id'), value.attr('data-amount'), 'shop_search', 1, csrf)
                    }
                } else {
                    const sug_price = parseFloat(value.find('.suggested-price').html().slice(1))
                    if(price+0.03 < _opdb_item_price && price < _opdb_item_price*0.55 && price < sug_price*0.65) {
                        console.log('hyper fast buy q1 '+price, _opdb_item_price, sug_price, market_hash_name)
                        buy_item(value.find('.btn.btn-success').attr('data-id'), value.attr('data-amount'), 'shop_search', 1, csrf)
                    }
                }
            } else {
                const sug_price = parseFloat(value.find('.suggested-price').html().slice(1))
                if(price+0.03 < sug_price && price < sug_price*0.45) {
                    console.log('hyper fast buy q1 '+price, sug_price, market_hash_name)
                    buy_item(value.find('.btn.btn-success').attr('data-id'), value.attr('data-amount'), 'shop_search', 1, csrf)
                }
            }
        })
    }

    function reload_items(cli) {
        let t_start = new Date().getTime()

        request({
            method: 'GET',
            proxy: cli.proxy,
            url: "https://opskins.com/ajax/browse_scroll.php?page=1&appId=1912&contextId=1",
            jar: cli.jar,
            headers: {
                'x-csrf': cli.csrf,
                'x-op-userid': '5329937',
                'x-requested-with': 'XMLHttpRequest',
                "referer": "https://opskins.com/?loc=shop_browse&app=1912_1",
                "user-agent": "Ubuntu Chromium/34.0.1847.116 Chrome/34.0.1847.116 Safari/537.36"
            },
            timeout: 600
        }, (error, response, body) => {
            if(!error) {
                let t_end = new Date().getTime()
                let diff = (t_end-t_start)

                //console.log(body)
                const $ = cheerio.load(body)
                load_prices($, cli.csrf, cli.jar, cli.proxy)

                let t_end2 = new Date().getTime()
                let diff2 = (t_end2-t_end)

                process.stdout.write("reload_items time: "+diff+" ms + "+diff2+" ms      \r")
            }
        })
    }
    //reload_items()
    //setInterval(reload_items, 5000)

    function buy_item(saleid, total, location, internal_search, csrf, j, proxy) {
        console.log(saleid, total, location, internal_search, csrf)
        request({
            method: 'POST',
            //proxy: proxy,
            url: "https://api.opskins.com/ICart/QuickBuy/v1/",
            //jar: j,
            headers: {
                //'x-csrf': csrf,
                //'x-op-userid': '5329937',
                //'x-requested-with': 'XMLHttpRequest',
                "user-agent": "Ubuntu Chromium/34.0.1847.116 Chrome/34.0.1847.116 Safari/537.36",
                'content-type': 'application/x-www-form-urlencoded; charset=UTF-8',
                cookie: "__cfduid=d5e1789657937e313d3f3573ffd250c601533420640; n_lang=en-US; timezone_offset=3%2C1; eu_cookie_accepted=auto; sale-graph-type=1; selectedApp=1912_1; machine_auth[5329937]=nzC0bxGqJ0SfD8GeDAMZp638aK706qz3; opskins_csrf_token=2qv4WTp2W7LZwtS7KG35cVLEDhx9XKM3C; PHPSESSID=ir5jipfomclbgufhi7lmsn97k4; opskins_login_token=MGL4nHfRWJ49dbgQcKnDQ8tgeRe08wCq; cf_clearance=0cc3a1ddfd5f9672b2102fc3a30968aac06c0d0b-1533664892-14400"
            },
            //form: { saleid, total, location, internal_search, csrf },
            body: 'saleid='+saleid+'&total='+total+'&location=shop_browse&internal_search=0&csrf=2qv4WTp2W7LZwtS7KG35cVLEDhx9XKM3C'
        }, (error, response, body) => {
            console.log('buy_item', error, body)
        })
    }



var op_lowest_prices = {}

function reload_prices(cli, cb) {
    request({
            method: 'GET',
            proxy: cli.proxy,
            url: "https://api.opskins.com/IPricing/GetAllLowestListPrices/v1/?appid=1912",
            jar: cli.jar,
            headers: {
                //'x-csrf': cli.csrf,
                //'x-op-userid': '5329937',
                //'x-requested-with': 'XMLHttpRequest',
                "referer": "https://opskins.com/?loc=shop_browse&app=1912_1",
                "user-agent": "Ubuntu Chromium/34.0.1847.116 Chrome/34.0.1847.116 Safari/537.36"
            }
    }, (error, response, body) => {
        if(!error && body.indexOf('403 Forbidden') == -1) {
            op_lowest_prices = JSON.parse(body).response
            cb()
            console.log('opskins prices loaded')
        } else {
            console.log(error, response, body)
        }
    })
}

var blacklist = {
    'M4A4 | Stripes (Field-Tested)': 0.65
}
