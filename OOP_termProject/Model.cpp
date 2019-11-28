#include<list>
#include"Object.cpp"
#include<string>
#include<fstream>
#include<iostream>
//바뀜
class Model {
	//book list선언(링크드리스트 - STL사용)
	std::list<Book> booklist;
	//person list선언(링크드리스트 - STL사용)
	std::list<person> personlist;

	//이터레이터
	std::list<Book>::iterator bklistItr = booklist.begin();
	std::list<person>::iterator pslistItr = personlist.begin();



	//로그인 check
	bool loginCheck(std::string id, std::string passwd) {
		//해당하는 id와 passwd가 일치하면 true리턴
		for (std::list<person>::iterator itr = personlist.begin(); itr != personlist.end(); itr++) {
			if ((*itr).getId() == id && (*itr).getPasswd() == passwd) {
				return true;
			}
		}

		//id와 passwd 둘 중 하나라도 틀리면 false리턴
		return false;
	}


	//book 추가
	bool bookInsert(std::string& addbookTitle, std::string& addauthor, std::string& addpublisher, int& addbookNumber) {
		//예외처리로 bookNumber가 같은 것이 있는지 확인
		for (std::list<Book>::iterator itr = booklist.begin(); itr != booklist.end(); itr++) {
			if ((*itr).getBookNumber() == addbookNumber) {
				return false;
			}
		}

		Book newbook(addbookTitle, addauthor, addpublisher, addbookNumber);
		booklist.push_back(newbook);
		
		return true;
	}

	//person 추가
	bool addPerson(std::string& name, std::string& id, std::string& passwd) {
		//예외처리로 id가 같은 것이 있는지 확인
		for (std::list<person>::iterator itr = personlist.begin(); itr != personlist.end(); itr++) {
			if ((*itr).getId() == id) {
				return false;
			}
		}

		person newPerson(name, id, passwd);
		personlist.push_back(newPerson);

		return true;
	}


	//book 검색
	std::list<Book> bookSearch(int givenBookNumber) {
		std::list<Book> aList;
		for (std::list<Book>::iterator iterPos = booklist.begin(); iterPos != booklist.end(); ++iterPos)
		{
			if ((*iterPos).getBookNumber() == givenBookNumber) {//주어진 것과 같은 책번호를 갖는 객체를 가리킬 때 작동
				Book abook((*iterPos).getBookTitle, (*iterPos).getAuthor, (*iterPos).getPublisher, (*iterPos).getBookNumber);//가리키는 객체를 복사
				abook.setLoan((*iterPos).getLoan);
				aList.push_back(abook);//반환할 리스트에 붙여넣기
			}
		}
		return aList;//리스트 반환
	}

	/*
	std::list<Book> bookSearch(std::string title  ) {

		bklistItr = booklist.begin();//초기화
		while (bklistItr != booklist.end()) {
			if ((*bklistItr).getBookTitle() == title) {
				return true;
			}
			++bklistItr;
		}
		bklistItr = booklist.begin();//찾는데 실패 시에 초기화 후 리턴
		return false;
	}
	*/

	bool bookSearchNum(int bookNum) {
		bklistItr = booklist.begin();

	}

	bool bookDelete(int bookNumber) {
		if (bookSearchNum(bookNumber)) {
			booklist.erase(bklistItr);
			return true;
		}
		return false;
	}
	
	bool bookLoan(std::string id, int bookNumber) {
		bklistItr = booklist.begin(); // 초기화 
		pslistItr = personlist.begin(); // 초기화 
		while (bklistItr != booklist.end()) { 
			if ((*bklistItr).getBookNumber() == bookNumber) { // 책이 있는지 확인
				while (pslistItr != personlist.end()) { 
					if ((*pslistItr).getId == id) { // id 같은 사람 찾기 
						int num = (*pslistItr).getLoanNumber;
						std::string settitle = std::to_string(bookNumber);
						// 권수가 1,2일때는 loanbook이 몇번째인지 모른다.
						if (num == 0) { // 책을 빌리지 않았을 때
							(*bklistItr).setLoan(true);
							(*pslistItr).setLoanNumber(1);
							(*pslistItr).setLoanBook1(settitle);
							return true;
						}
						else if (num == 1) { // 한권 빌렸을 때 
							// 뭐가 빌렸는지 확인 
							if ((*pslistItr).getLoanBook1 != "") {
								(*bklistItr).setLoan(true);
								(*pslistItr).setLoanNumber(2);
								(*pslistItr).setLoanBook2(settitle);
								return true;
							}
							else if ((*pslistItr).getLoanBook2 != "") {
								(*bklistItr).setLoan(true);
								(*pslistItr).setLoanNumber(2);
								(*pslistItr).setLoanBook1(settitle);
								return true;
							}
							else if ((*pslistItr).getLoanBook3 != "") {
								(*bklistItr).setLoan(true);
								(*pslistItr).setLoanNumber(2);
								(*pslistItr).setLoanBook1(settitle);
								return true;
							}
						}
						else if (num == 2) { // 두권 빌렸을 때
							// 뭐가 안빌렸는지 확인 
							if ((*pslistItr).getLoanBook1 == "") {
								(*bklistItr).setLoan(true);
								(*pslistItr).setLoanNumber(3);
								(*pslistItr).setLoanBook1(settitle);
								return true;
							}
							else if ((*pslistItr).getLoanBook2 == "") {
								(*bklistItr).setLoan(true);
								(*pslistItr).setLoanNumber(3);
								(*pslistItr).setLoanBook2(settitle);
								return true;
							}
							else if ((*pslistItr).getLoanBook3 == "") {
								(*bklistItr).setLoan(true);
								(*pslistItr).setLoanNumber(3);
								(*pslistItr).setLoanBook3(settitle);
								return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	// 반납
	bool bookReturn(std::string id, int bookNumber) {
		bklistItr = booklist.begin(); // 초기화 
		pslistItr = personlist.begin(); // 초기화 

		while (bklistItr != booklist.end())
		{
			if ((*bklistItr).getBookNumber == bookNumber) { 
				if ((*bklistItr).getLoan == true) { // 책이 대출 상태인지 확인 
					std::string gettitle = std::to_string(bookNumber);
					while (pslistItr != personlist.end())
					{
						if ((*pslistItr).getId == id) { // 아이디 확인 
							int num = (*pslistItr).getLoanNumber(); // 대출 권수 확인 
							if (num == 1) {
								if ((*pslistItr).getLoanBook1 == gettitle) { // 반납할 책과 대출한 책이 일치하는지 확인 
									(*pslistItr).setLoanBook1(NULL);
									(*pslistItr).setLoanNumber = 0;
									(*bklistItr).setLoan = false;
									return true;
								}
							}
							else if (num == 2) {
								if ((*pslistItr).getLoanBook1 == gettitle) {
									(*pslistItr).setLoanBook1(NULL);
									(*pslistItr).setLoanNumber = 1;
									(*bklistItr).setLoan = false;
									return true;
								}
								else if ((*pslistItr).getLoanBook2 == gettitle) {
									(*pslistItr).setLoanBook2(NULL);
									(*pslistItr).setLoanNumber = 1;
									(*bklistItr).setLoan = false;
									return true;
								}
							}
							else if (num == 3) {
								if ((*pslistItr).getLoanBook1 == gettitle) {
									(*pslistItr).setLoanBook1(NULL);
									(*pslistItr).setLoanNumber = 2;
									(*bklistItr).setLoan = false;
									return true;
								}
								else if ((*pslistItr).getLoanBook2 == gettitle) {
									(*pslistItr).setLoanBook2(NULL);
									(*pslistItr).setLoanNumber = 2;
									(*bklistItr).setLoan = false;
									return true;
								}
								else if ((*pslistItr).getLoanBook3 == gettitle) {
									(*pslistItr).setLoanBook3(NULL);
									(*pslistItr).setLoanNumber = 2;
									(*bklistItr).setLoan = false;
									return true;
								}
							}
						}
					}
				
				}
			}
		}
		return false;
	}

	//person 삭제
	bool personDelete(std::string id) {
		
		//id 검사
		for (std::list<person>::iterator itr = personlist.begin(); itr != personlist.end(); itr++) {
			if ((*itr).getId() == id) {
				personlist.erase(itr);
				return true;
			}
		}

		//찾는 id가 없으면 false리턴
		return false;
	}

	std::string file_to_string(std::string filePath) {
		std::ifstream in(filePath);
		std::string s;

		if (in.is_open()) {
			// 위치 지정자를 파일 끝으로 옮긴다.
			in.seekg(0, std::ios::end);

			// 그리고 그 위치를 읽는다. (파일의 크기)
			int size = in.tellg();

			// 그 크기의 문자열을 할당한다.
			s.resize(size);

			// 위치 지정자를 다시 파일 맨 앞으로 옮긴다.
			in.seekg(0, std::ios::beg);

			// 파일 전체 내용을 읽어서 문자열에 저장한다.
			in.read(&s[0], size);

			in.close();//파일 닫음
			return s;
		}
	}
public:
	void makeBookList(std::string givenString) {			//사용예시: makeBookList(file_to_string("book.txt"));
		std::string line;
		while (givenString)
		{
			std::string title;
			std::string author;
			std::string publisher;
			int bookNumber;
			int beforIntToBool;
			
			std::getline(givenString, line, \n);
			std::istream ss(line);
			std::string buffer, value;
			
			std::getline(ss, buffer, '|');
			value = buffer;
			title = value;

			std::getline(ss, buffer, '|');
			value = buffer;
			author = value;

			std::getline(ss, buffer, '|');
			value = buffer;
			publisher = value;

			std::getline(ss, buffer, '|');
			value = atoi(buffer.c_str());//정수로 변환
			bookNumber = value;

			std::getline(ss, buffer, '|');
			value = atoi(buffer.c_str());//일단 정수로 변환
			beforIntToBool = value;

			Book book(title, author, publisher, bookNumber);
			if (beforIntToBool == 1) {								//수동 형변환
				book.setLoan(true);
			}
			else {
				book.setLoan(false);
			}

			booklist.push_back(book);
		}
	}

public:
	void makePersonList(std::string givenString) {
		std::string line;
		while (givenString)//한줄 읽어서 객체 만들고 리스트에 푸시. 문자열 끝까지. \\\\ 매개변수 수정 필요?
		{
			std::string name;
			std::string id;
			std::string passwd;
			int loanNumber;
			std::string loanBook1;
			std::string loanBook2;
			std::string loanBook3;

			std::getline(givenString, line, \n);
			istream ss(line);
			string buffer, value;

			std::getline(ss, buffer, '|');
			value = buffer;
			name = value;

			std::getline(ss, buffer, '|');
			value = buffer;
			id = value;

			std::getline(ss, buffer, '|');
			value = buffer;
			passwd = value;

			std::getline(ss, buffer, '|');
			value = atoi(buffer.c_str());//정수로 변환
			loanNumber = value;

			std::getline(ss, buffer, '|');
			value = buffer;
			loanBook1 = value;

			std::getline(ss, buffer, '|');
			value = buffer;
			loanBook2 = value;

			std::getline(ss, buffer, '|');
			value = buffer;
			loanBook3 = value;

			person person(name, id, passwd);
			person.setLoanNumber(loanNumber);
			person.setLoanBook1(loanBook1);
			person.setLoanBook2(loanBook2);
			person.setLoanBook3(loanBook3);


			personlist.push_back(person));
		}
	}
		/*
	public:
		void dataInit() {
			//파일입출력으로 booklist에 파일의 책데이터를 푸시(초기실행시 1번만 실행)
			//파일입출력으로 personlist에 파일의 사람데이터를 푸시(초기실행시 1번만 실행)
		}
		*/														//더이상 쓰이지 않음. file_to_string 로 사용할것.

public:
	std::string booklist_to_string() {
		std::string result;
		for (std::list<Book>::iterator itr = booklist.begin(); itr != booklist.end(); itr++) {
			std::string title = (*itr).getBookTitle();
			std::string author = (*itr).getAuthor();
			std::string publisher = (*itr).getPublisher();
			std::string  bookNumber = std::to_string((*itr).getBookNumber());
			bool beforBoolToInt = (*itr).getLoan;
			std::string loan;

			if (beforBoolToInt == true) {
				loan = "1";
			}
			else {
				loan = "0";
			}
			
			result = result + title + "|" + author + "|" + publisher + "|" + bookNumber + "|" + loan + "\n";

		}
	}
public:
	std::string personlist_to_string() {
		std::string result = "";
		for (std::list<person>::iterator itr = personlist.begin(); itr != personlist.end(); itr++) {
			std::string name = (*itr).getName();
			std::string id = (*itr).getId;
			std::string passwd = (*itr).getPasswd;
			std::string loanNumber = std::to_string((*itr).getLoanNumber;
			std::string loanBook1 = (*itr).getLoanBook1;
			std::string loanBook2 = (*itr).getLoanBook2;
			std::string loanBook3 = (*itr).getLoanBook3;

			result = result + name + "|" + id + "|" + passwd + "|" + loanNumber + "|" + loanBook1 + "|" + loanBook2 + "|" + loanBook3 + "\n";

		}
		return result;
	}
	void string_to_file(std::string bookString, std::string personString) {//파일 업데이트. 프로그램 종료 시 반드시 수행할것. 예): string_to_file(booklist_to_string(), personlist_to_string());
		std::fstream out;
		out.open("booklist.txt", std::ios_base::out | std::ios_base::trunc);	//파일 초기화하고 쓰기모드로 열기

		if (out.is_open()) {
			out << bookString;										//파일에 새 내용 저장
			out.close();
		}

		out.open("personlist.txt", std::ios_base::out | std::ios_base::trunc);

		if (out.is_open()) {
			out << personString;
			out.close();
		}
	}
	

};
