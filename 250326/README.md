# 언리얼 플러그인 제작

- 팀에서 협업을 하는 방법 중 하나 인 플러그인 제작 실습

## 새 프로젝트 만들기
1. 플러그인 제작을 위한 새로운 프로젝트 생성

## 새 플러그인 만들기
1. Edit ⇒ Plugins를 선택해서 Plugins 윈도우를 생성하고, +ADD 버튼을 클릭

## 플러그인 종류와 이름 정하기 
1. Blueprint Library로 만들고 MyIDPlugin으로 이름 지정

## 생성된 파일 확인하기
1. Blueprint library 플러그인은 소스 파일이 4개 생성됨
2. MyIDPlugin.h / MyIDPlugin.cpp / MyIDPluginBPLibrary.h / MyIDPluginBPLibrary.cpp

## 기능 정의하기 
1. UserID를 저장하는 기능과 저장된 값을 읽어오는 2가지를 구현
2. void SetUserName(const FString& NewName) : 이름을 저장하는 기능
3. FString GetUserName() : 이름을 가져오는 기능

## 코드 채우기 
1. MyIDPluginBPLibrary.cpp에 해당 함수를 작성

## Package 하기 
1. 배포할 수 있도록 패키지로 제작

## 에디터에서 플러그인 활성화하기 
1. 에디터에서 플러그인을 활성화해서 사용할 수 있도록 조치

