/*
David Pierce & Ben Walker
Milestone 2
Database: cs5021team10
*/

/* ---- Create scripts ---- */

CREATE TABLE applicant (
    applicant_id    int NOT NULL UNIQUE AUTO_INCREMENT,
    date_of_birth   date NOT NULL,
    address_street  varchar(60) NOT NULL,
    address_city    varchar(20) NOT NULL,
    us_state_id     int NOT NULL,
    address_zip     char(5) NOT NULL,
    phone_number    char(11) NOT NULL,
    us_citizen      boolean NOT NULL,
    english_native  boolean,
    hispanic        boolean,
    gender_id       int,
    veteran_id      int,
    military_branch_id  int,
    student_type_id int,
    major_id        int,
    term_id         int,
    financial_aid   boolean,
    tuition_assist  boolean,
    apply_other     boolean,
    convicted       boolean,
    probation       boolean,
    PRIMARY KEY (applicant_id)
) ENGINE = INNODB;

CREATE TABLE name_type (
    name_type       char(1) NOT NULL,
    name_descr      varchar(12) NOT NULL,
    PRIMARY KEY (name_type)
) ENGINE = INNODB;

CREATE TABLE name (
    name_id         int NOT NULL UNIQUE AUTO_INCREMENT,
    name_value      varchar(50) NOT NULL,
    name_type       char(1) NOT NULL,
    PRIMARY KEY (name_id),
    FOREIGN KEY (name_type) REFERENCES name_type (name_type) ON UPDATE CASCADE
) ENGINE = INNODB;

CREATE TABLE applicant_name (
    applicant_id    int NOT NULL,
    name_id         int NOT NULL,
    PRIMARY KEY (applicant_id, name_id),
    FOREIGN KEY (applicant_id) REFERENCES applicant (applicant_id) ON UPDATE CASCADE,
    FOREIGN KEY (name_id) REFERENCES name (name_id) ON UPDATE CASCADE
) ENGINE = INNODB;

CREATE TABLE us_state (
us_state_id INT NOT NULL UNIQUE AUTO_INCREMENT,
us_state_name VARCHAR(50) NOT NULL,
PRIMARY KEY ( us_state_id )
) ENGINE = INNODB;

CREATE TABLE gender (
gender_id INT NOT NULL AUTO_INCREMENT,
gender_name VARCHAR(20) NOT NULL,
PRIMARY KEY ( gender_id )
) ENGINE = INNODB;

CREATE TABLE employer (
employer_id INT NOT NULL UNIQUE AUTO_INCREMENT,
employer_name VARCHAR(50),
employer_address_street VARCHAR(25),
us_state_id INT NOT NULL,
employer_address_zip VARCHAR(10),
PRIMARY KEY ( employer_id ),
FOREIGN KEY ( us_state_id ) REFERENCES us_state ( us_state_id ) ON UPDATE CASCADE
) ENGINE = INNODB;

CREATE TABLE applicant_employement (
applicant_id INT NOT NULL,
employer_id INT NOT NULL,
start_date DATE NOT NULL,
end_date DATE,
currently_employed BOOLEAN NOT NULL,
job_title VARCHAR(25),
full_time BOOLEAN,
PRIMARY KEY (applicant_id, employer_id, start_date),
FOREIGN KEY (applicant_id) REFERENCES applicant (applicant_id) ON UPDATE CASCADE,
FOREIGN KEY (employer_id) REFERENCES employer (employer_id) ON UPDATE CASCADE
) ENGINE = INNODB;

CREATE TABLE education_history (
education_history_id INT NOT NULL UNIQUE AUTO_INCREMENT,
applicant_id INT NOT NULL,
institution VARCHAR(50) NOT NULL,
attended_from DATE NOT NULL,
attended_to DATE NOT NULL,
major VARCHAR(50) NOT NULL,
degree VARCHAR(50),
date_received DATE,
PRIMARY KEY ( education_history_id, applicant_id ),
FOREIGN KEY ( applicant_id ) REFERENCES applicant ( applicant_id ) ON UPDATE CASCADE
) ENGINE = INNODB;

CREATE TABLE test (
test_id INT NOT NULL UNIQUE AUTO_INCREMENT,
test_name VARCHAR(50) NOT NULL,
PRIMARY KEY ( test_id )
) ENGINE = INNODB;

CREATE TABLE applicant_test (
applicant_id INT NOT NULL,
test_id INT NOT NULL,
test_date DATE NOT NULL,
test_score VARCHAR(10),
PRIMARY KEY ( applicant_id, test_id, test_date ),
FOREIGN KEY ( applicant_id ) REFERENCES applicant ( applicant_id ) ON UPDATE CASCADE,
FOREIGN KEY ( test_id ) REFERENCES test ( test_id ) ON UPDATE CASCADE
) ENGINE = INNODB;

CREATE TABLE ethnicity (
    ethnicity_id    int NOT NULL UNIQUE AUTO_INCREMENT,
    ethnicity_name  varchar(50) NOT NULL,
    PRIMARY KEY (ethnicity_id)
) ENGINE = INNODB;

CREATE TABLE applicant_ethnicity (
    applicant_id    int NOT NULL,
    ethnicity_id    int NOT NULL,
    PRIMARY KEY (applicant_id, ethnicity_id),
    FOREIGN KEY (applicant_id) REFERENCES applicant (applicant_id) ON UPDATE CASCADE,
    FOREIGN KEY (ethnicity_id) REFERENCES ethnicity (ethnicity_id) ON UPDATE CASCADE
) ENGINE = INNODB;

CREATE TABLE veteran (
    veteran_id      int NOT NULL UNIQUE AUTO_INCREMENT,
    veteran_status  varchar(20) NOT NULL,
    PRIMARY KEY (veteran_id)
) ENGINE = INNODB;

CREATE TABLE military_branch (
    military_branch_id      int NOT NULL UNIQUE AUTO_INCREMENT,
    military_branch_name    varchar(20) NOT NULL,
    PRIMARY KEY (military_branch_id)
) ENGINE = INNODB;

CREATE TABLE student_type (
    student_type_id         int NOT NULL UNIQUE AUTO_INCREMENT,
    student_type_name       varchar(30) NOT NULL,
    PRIMARY KEY (student_type_id)
) ENGINE = INNODB;

CREATE TABLE college (
    college_id      int NOT NULL UNIQUE AUTO_INCREMENT,
    college_name    varchar(80) NOT NULL,
    PRIMARY KEY (college_id)
) ENGINE = INNODB;

CREATE TABLE major (
    major_id        int NOT NULL UNIQUE AUTO_INCREMENT,
    major_name      varchar(80) NOT NULL,
    college_id      int NOT NULL,
    PRIMARY KEY (major_id),
    FOREIGN KEY (college_id) REFERENCES college (college_id)
) ENGINE = INNODB;

CREATE TABLE degree_type (
    degree_type_id      int NOT NULL UNIQUE AUTO_INCREMENT,
    degree_type_name    varchar(80) NOT NULL,
    PRIMARY KEY (degree_type_id)
) ENGINE = INNODB;

CREATE TABLE college_degree (
    college_id      int NOT NULL,
    degree_type_id  int NOT NULL,
    PRIMARY KEY (college_id, degree_type_id),
    FOREIGN KEY (college_id) REFERENCES college (college_id),
    FOREIGN KEY (degree_type_id) REFERENCES degree_type (degree_type_id)
) ENGINE = INNODB;

CREATE TABLE term (
    term_id     int NOT NULL UNIQUE AUTO_INCREMENT,
    term_name   varchar(30) NOT NULL,
    PRIMARY KEY (term_id)
) ENGINE = INNODB;

/* ---- Foreign Key Relations for applicant ---- */

ALTER TABLE applicant ADD (
    FOREIGN KEY (us_state_id) REFERENCES us_state (us_state_id) ON UPDATE CASCADE,
    FOREIGN KEY (gender_id) REFERENCES gender (gender_id) ON UPDATE CASCADE,
    FOREIGN KEY (veteran_id) REFERENCES veteran (veteran_id) ON UPDATE CASCADE,
    FOREIGN KEY (military_branch_id) REFERENCES military_branch (military_branch_id) ON UPDATE CASCADE,
    FOREIGN KEY (student_type_id) REFERENCES student_type (student_type_id) ON UPDATE CASCADE,
    FOREIGN KEY (major_id) REFERENCES major (major_id) ON UPDATE CASCADE,
    FOREIGN KEY (term_id) REFERENCES term (term_id) ON UPDATE CASCADE
);

/* ---- Insert scripts ---- */

INSERT INTO name_type VALUES
('F','First'),
('M','Middle'),
('L','Last'),
('P','Preferred');

INSERT INTO student_type (student_type_name) VALUES
('Graduate'),
('Graduate Non-Matriculated'),
('Graduate Readmission');

INSERT INTO college (college_name) VALUES
('College of Science and Engineering'),
('Albers School of Business'),
('College of Arts and Sciences'),
('College of Education'),
('College of Nursing'),
('School of Theology and Ministry');

INSERT INTO major (major_name, college_id) VALUES
('Certificate in Computer Science Fundamentals',1),
('Certificate in Software Architecture and Design',1),
('Certificate in Software Project Management',1);

INSERT INTO degree_type (degree_type_name) VALUES
('Certificates'),
('Masters');

INSERT INTO term (term_name) VALUES
('Summer 2016'),
('Fall 2016'),
('Winter 2017'),
('Spring 2017');

INSERT INTO gender (gender_name) VALUES
('Not defined'),
('Female'),
('Male');

INSERT INTO veteran (veteran_status) VALUES
('Not a veteran'),
('Currently serving'),
('Previously served'),
('Current dependent');

INSERT INTO military_branch (military_branch_name) VALUES
('N/A'),
('Army'),
('Marine Corp'),
('Navy'),
('Air Force'),
('Coast Guard');

INSERT INTO ethnicity (ethnicity_name) VALUES
('Asian'),
('Black/African American'),
('Native Hawaiian/Pacific Islander'),
('Native American/Native Indian'),
('White/Middle Eastern');

INSERT INTO test (test_name) VALUES
('CBEST'),
('GMAT'),
('GRE General'),
('IELTS'),
('MAT'),
('PRAXIS'),
('TOEFL'),
('WEST-B'),
('WEST-E');

INSERT INTO us_state (us_state_name) VALUES
('Alabama'),
('Alaska'),
('Arizona'),
('Arkansas'),
('California'),
('Colorado'),
('Connecticut'),
('Delaware'),
('Florida'),
('Georgia'),
('Hawaii'),
('Idaho'),
('Illinois'),
('Indiana'),
('Iowa'),
('Kansas'),
('Kentucky'),
('Louisiana'),
('Maine'),
('Maryland'),
('Massachusetts'),
('Michigan'),
('Minnesota'),
('Mississippi'),
('Missouri'),
('Montana'),
('Nebraska'),
('Nevada'),
('New Hampshire'),
('New Jersey'),
('New Mexico'),
('New York'),
('North Carolina'),
('North Dakota'),
('Ohio'),
('Oklahoma'),
('Oregon'),
('Pennsylvania'),
('Rhode Island'),
('South Carolina'),
('South Dakota'),
('Tennessee'),
('Texas'),
('Utah'),
('Vermont'),
('Virginia'),
('Washington'),
('West Virginia'),
('Wisconsin'),
('Wyoming');
