---
layout: post
title: '[일상] 블로그에 Search 기능 구현 도전기'
author: wookje.kwon
comments: true
date: 2017-02-15 20:00
tags: [daily, develop, web]
---

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

아니 무려 카카오에서 일하시는 분들이 검색을 짜기가 귀찮아서 웹으로 넘겼다고? 그럼 내가 한 번 해보지!  
잘은 모르지만 대충 배껴서 만들면 아마 돌아갈거야 ~~재앙의 시작~~  

<img src="/files/search00.png" width="640" height="360">  
룰루   

<img src="/files/search01.png" width="640" height="360">  
랄라~  

과정이 더 있지만 캡쳐하기 귀찮으므로 생략  

<img src="/files/search02.png" width="640" height="360">  
이제 돌아가겠지?  

<img src="/files/search03.png" width="450" height="360">   
으아아아아아아아아  

그렇게 똑같은 파일 수십번씩 확인하고 commit 30번에 별짓 다 해봤는데  
범인은 사이트맵이었다 (...)  

```xml
  <!--for tag in site.tags-->
  <url>
    <loc>{{ site.url }}{{ site.baseurl }}/tags/{{ tag.name }}</loc>
    <changefreq>monthly</changefreq>
    <priority>0.8</priority>
  </url>
  <!--endfor-->
```

삽질 할 거 다 하고나서 깨달은 사실인데, 저런 식으로 사이트맵을 직접 만들어야 하더라.  

나는 웹알못이라 고오급 코딩은 못하고  
있는 소스 배껴서 써먹어야하는데  
있는 소스는 baseurl에다가 경로 붙이는(?) 형식으로 구현되어 있다 ㅠㅠ  
그러려면 사이트맵이 미리 구성되어야 하는데, 무슨 단어로 검색할 줄 알고 사이트맵을 일일히 다 만들어 ㅠㅠ   

결국 다시 rebase해서  

```js
$('#search').submit(function (e) {
	e.preventDefault();
    var q = $('#searchQueryEdit').val();
    var url = 'https://www.google.co.kr/webhp?sourceid=chrome-instant&ion=1&espv=2&ie=UTF-8#q='
          + encodeURIComponent(q + ' site:wookje.github.com');
    window.open(url, '', '_blank');
});
```

검색엔진만 google로 바뀌고 원래대로 돌아왔다.  
정말 슬픈 일이다.  

여담이지만 위에 backquote로 xml 소스 올리는데 저게 컴파일(?)이 돼버려서  
진짜로 tags를 출력해버리더라 ㅋㅋㅋㅋ    
웹의 세계는 알다가도 모르겠다  
전국에 계신 웹개발자 여러분 존경합니다  

그리고 웹 짜면서 소스에 에러 있어도 돌아가는 거 보고 충격받았다.  
완전하고 안전한 상태를 추구하는 PL에 길들여진 나로서는 웹을 도저히 이해할 수 없다 (...)  

맞다 댓글창 사이즈도 맞춰야 되는데 어떻게 하는 거지  

블로그에 Search 기능 구현 도전기 - 끝  
