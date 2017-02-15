----
layout: post
title: '[일상] 블로그에 search 구현해보기'
author: wookje.kwon
comments: true
date: 2017-02-15 19:31
tags: [daily, develop, web]

----

약 2시간 정도 삽질했는데, 결론부터 말하자면 구현은 **실패** 했다.  

사실 이 블로그가 [카카오 테크 블로그](http://tech.kakao.com/)에서 따온 블로그인데,  
원래 검색 기능은 이렇게 구현되어 있었다:  

```js
$('#search').submit(function (e) {
    e.preventDefault();
    var q = $('#searchQueryEdit').val();
    var url = 'http://search.daum.net/search?q=' + encodeURIComponent(q + ' site:tech.kakao.com');
    window.open(url, '', '_blank');
});
```

아니 무려 카카오에서 일하시는 분들이 검색을 짜기가 귀찮아서 웹으로 넘겼다고?  

순진한 웹알못이었던 나는 아무것도 모른 채 야매로 search를 만들어보려고 했다. ~~재앙의 시작~~  

웹은 몰랐지만 다른 페이지(tags, author)가 구현된 걸 보고 복붙해서 만들려고 했다. ~~sitemap을 미리 알았더라면..~~  

<img width="600" height="400">![search00](/files/search00.png)</img>  

yaml 파일도 수정하고  

<img width="600" height="400">![search00](/files/search01.png)</img>  

search.md도 만들고  

