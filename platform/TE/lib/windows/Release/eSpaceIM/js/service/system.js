
define(["require", "util/util", "i18n/zh-cn", "i18n/en-us", "i18n/fr-fr"], function(require, util){
    
    var guid = util.now(),
    
    info = {
        account: "",            
        name: "",               
        lang: "",               
        customScrollbar: false, 
        joinRecord: false,      
        timeDiff: 10000,        
        scrollbarAtBottom: true     
    },
    
    langMapping = {
        "1033": "en-us",
        "2052": "zh-cn",
		"1036": "fr-fr",
		"1046": "en-us",
		"2070": "en-us",
		"3082": "en-us",
		"1041": "en-us"
    } ;
    
    function init(options)
    {
        for(var i in options)
        {
            info[i] = options[i] ;
        }
        

        if(navigator.appName == "Microsoft Internet Explorer" 
            && navigator.appVersion.split(";")[1].replace(/[ ]/g,"") == "MSIE6.0") 
        { 
            info.isIE6 = true ;
        }
        else
        {
            info.isIE6 = false ;
        }
    }

    function getGuid()
    {
        guid++ ;
        
        return guid ;
    }
    

    function getInfo()
    {
        return info ;
    }
    

    function getLang()
    {
        return require("i18n/" + langMapping[info.lang]) ;
    }

    function joinRecord(record, preRecord)
    {
        return info.joinRecord 
                && (new Date(record.time.replace(/\-/g, "/"))).getTime() - (new Date(preRecord.time.replace(/\-/g, "/"))).getTime() <= info.timeDiff
                && record.account == preRecord.account ;
    }
    
    return {
        init: init,
        getGuid: getGuid,
        getLang: getLang,
        getInfo: getInfo,
        joinRecord: joinRecord
    } ;
    
}) ;