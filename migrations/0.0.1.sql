BEGIN;

CREATE TABLE users (
  id bigserial NOT NULL PRIMARY KEY,
  username varchar(64) UNIQUE NOT NULL,
  first_name varchar(64) NOT NULL,
  last_name varchar(64) NOT NULL,
  patronymic varchar(64),
  password varchar(128) NOT NULL,
  creation_time timestamp NOT NULL DEFAULT NOW()
);

CREATE TABLE sessions (
  id bigserial NOT NULL PRIMARY KEY,
  id_user bigint NOT NULL,
  session varchar(128) DEFAULT NULL,
  FOREIGN KEY (id_user) REFERENCES users (id)
);

CREATE TABLE user_groups (
  id bigserial NOT NULL PRIMARY KEY,
  name varchar(64) NOT NULL,
  creation_time timestamp NOT NULL DEFAULT NOW(),
  is_local boolean NOT NULL DEFAULT FALSE
);

CREATE TABLE user_user_groups (
  id serial NOT NULL PRIMARY KEY,
  id_user bigint NOT NULL,
  id_user_group bigint NOT NULL,
  is_admin boolean NOT NULL DEFAULT FALSE,
  FOREIGN KEY (id_user) REFERENCES users (id),
  FOREIGN KEY (id_user_group) REFERENCES user_groups (id)
);

CREATE TABLE task_groups (
  id bigserial NOT NULL PRIMARY KEY,
  id_user_group bigint NOT NULL,
  name varchar(64) NOT NULL,
  creation_time timestamp NOT NULL DEFAULT NOW(),
  FOREIGN KEY (id_user_group) REFERENCES user_groups (id)
);

CREATE TABLE places (
  id bigserial NOT NULL PRIMARY KEY,
  location int  NOT NULL default 0
);

CREATE TABLE tasks (
  id bigserial NOT NULL PRIMARY KEY,
  id_task_group bigint NOT NULL,
  id_user bigint NOT NULL,
  id_place bigint NOT NULL,
  is_finished boolean NOT NULL DEFAULT FALSE,
  time_planned timestamp,
  time_doing_task interval NOT NULL DEFAULT '15 minutes',
  time_deadline timestamp,
  time_change timestamp NOT NULL DEFAULT NOW(),
  title varchar(64) NOT NULL,
  description text,
  priority int NOT NULL DEFAULT 3,
  creation_time timestamp NOT NULL DEFAULT NOW(),
  FOREIGN KEY (id_task_group) REFERENCES task_groups (id),
  FOREIGN KEY (id_user) REFERENCES users (id),
  FOREIGN KEY (id_place) REFERENCES places (id)
);

COMMIT;
