# TEXT RPG 프로젝트 담당 코드 업로드

- 몬스터 관련 로직 구현
- 피드백 사항 : 모든 코드의 일관성을 통일 시키는 작업 필요, CreateMonsterInfo 함수 불필요 판단시 제거 필요

# Monster Class : public Entity

- struct FMonsterInfo; : 몬스터 정보를 담아서 생성자로 넘겨주기 위한 구조체
- static unordered_map<string, int> DeathCountMap; : 몬스터 이름별로 죽은 횟수를 저장 후 이를 출력하기 위한 맵 변수
- int Difficulty; : 몬스터 난이도 저장 변수
- Monster(string Name, int Hp, int Damage, int Difficulty, EDraw Draw); : 몬스터 정보 및 난이도에 맞는 몬스터를 생성하기 위한 생성자
- static FMonsterInfo CreateMonsterInfo(int PlayerLevel, int Difficulty); : 플레이어 레벨 및 선택 난이도에 맞는 몬스터의 이름, 체력, 공격력 정보 생성 함수
- void TakeDamage(int Damage); : 입력값만큼 해당 몬스터 HP 차감을 위한 함수
- static void PrintAllDeathCounts(); : 모든 몬스터의 죽은 횟수를 출력하는 함수

# PPT 포함 내용 정리

몬스터를 담당해서 구현하였습니다. 쉬움, 보통, 어려움에 해당하는 난이도의 몬스터를 생성할 수 있고 각 몬스터의 죽은 횟수도 확인할 수 있습니다.

### FMonsterInfo CreateMonsterInfo 함수

플레이어 레벨 및 선택 난이도에 맞는 몬스터의 이름, 체력, 공격력 정보를 생성할 수 있는 함수입니다.  
Monster 생성자에 이름, 체력, 공격력을 넘겨주기 위해서 FMonsterInfo 라는 구조체 값을 리턴하도록 구현하였습니다.

![image](https://github.com/user-attachments/assets/bfd568ec-63ca-4135-b252-de5cfaadbfc3)

### Monster 생성자

상속받은 Entity 클래스에 있는 이름, 체력, 공격력 변수에 그대로 값을 넣기위하여 해당 값을 받는 형태로 구현하였습니다.  
Difficulty와 Draw는 각각 해당 몬스터의 난이도 및 그림을 위한 데이터입니다.

![image](https://github.com/user-attachments/assets/2cbee39b-ff1b-4dca-9783-f41535237e51)

### void TakeDamage 함수

몬스터가 피해를 입을때마다 해당 값을 계산하고 몬스터가 죽으면 배틀 종료 이후에 모든 몬스터의 죽은 횟수를 출력하기 위하여  
unordered_map<string, int> DeathCountMap 변수를 사용하여 각 몬스터의 죽은 횟수를 저장합니다.

![image](https://github.com/user-attachments/assets/2ab8335b-51aa-42b9-b507-3c19690ab66b)

1. 난이도에 맞는 몬스터가 제대로 생성되는지, 몬스터의 HP가 정상적으로 차감되는지, 죽은 몬스터의 횟수가 정상적으로 누적되는지 확인 완료
2. Entity 클래스 상속 이후 Name, HP, Damage 부분을 이용한 몬스터 생성자 구현 및 각 몬스터의 죽은 횟수 저장을 위한 unordered_map 사용
3. 랜덤 몬스터 생성 및 몬스터의 공격 및 피격 결과 확인, 보스 몬스터 소환 확인, 전투 종료 후 각 몬스터의 죽은 횟수 출력 여부까지 확인 완료
4. 필수 기능 : 랜덤으로 몬스터 생성 및 몬스터 스펙이 캐릭터 레벨에 비례해서 랜덤하게 생성되도록 구현 및 로그를 통해 각 몬스터의 죽은 횟수 확인 완료
5. 도전 기능 : 요구 사항에 해당하는 보스 몬스터 생성 작업 완료

# Bug Fix 1

- 플레이어 선택에 따른 몬스터 선택 과정에서 몬스터 배열 범위를 벗어나서 접근하는 문제 발생
- 플레이어 선택에 + 1번이 상점 선택인데 해당 번호를 선택시 문제 발생
- 상점을 선택하는 경우만 예외 처리 형태로 해결

# Bug Fix 2

- 보스 몬스터 처치 이후에 프로그램이 끝나지 않고 밑에 코드가 전부 실행된 이후에 게임이 끝나는 문제 발생
- exit(0) 함수를 이용하여 보스 전투 이후 강제로 프로그램 종료되게끔 구현 후 해결
