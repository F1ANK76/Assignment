# TEXT RPG 프로젝트 담당 코드 업로드

- 몬스터 관련 로직 구현
- 피드백 사항 : 모든 코드의 일관성을 통일 시키는 작업 필요, CreateMonsterInfo 함수 불필요 판단시 제거 필요

# Monster Class : public Entity

- struct FMonsterInfo; : 몬스터 정보를 담은 구조체
- int Difficulty; : 몬스터 난이도 선언 변수
- Monster(string Name, int Hp, int Damage, int Difficulty); : 몬스터 정보 및 난이도에 맞는 몬스터 생성자
- static FMonsterInfo CreateMonsterInfo(int PlayerLevel, int Difficulty); : 플레이어 레벨 및 선택 난이도에 맞는 몬스터의 이름, 체력, 공격력 정보 생성
- void TakeDamage(int Damage); : 입력값만큼 해당 몬스터 HP 차감
- int GetDifficulty(); : 해당 몬스터의 난이도 값을 반환하는 Getter 함수

# PPT 포함 내용 정리

1. 난이도에 맞는 몬스터가 제대로 생성되는지, 몬스터의 HP가 정상적으로 차감되는지 확인 완료
- 2. Entity 클래스를 상속받아서 Entity 생성자의 Name, HP, Damage 부분을 사용해서 몬스터 생성자 구현
- 3. 랜덤 몬스터 생성 및 몬스터의 공격 및 피격 결과 확인, 보스 몬스터 소환 부분까지 확인 완료
- 4-1. 필수 기능 : 랜덤으로 몬스터 생성 및 몬스터 스펙이 캐릭터 레벨에 비례해서 랜덤하게 생성되도록 구현 완료
- 4-2. 도전 기능 : 보스 몬스터 생성 작업 완료

# Bug Fix 1

- 플레이어 선택에 따른 몬스터 선택 과정에서 몬스터 배열 범위를 벗어나서 접근하는 문제 발생
- 플레이어 선택에 + 1번이 상점 선택인데 해당 번호를 선택시 문제 발생
- 상점을 선택하는 경우만 예외 처리 형태로 해결

# Bug Fix 2

- 보스 몬스터 처치 이후에 프로그램이 끝나지 않고 밑에 코드가 전부 실행된 이후에 게임이 끝나는 문제 발생
- exit(0) 함수를 이용하여 보스 전투 이후 강제로 프로그램 종료되게끔 구현 후 해결
