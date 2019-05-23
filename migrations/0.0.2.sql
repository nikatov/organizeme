INSERT INTO users (username, first_name, last_name, password)
VALUES ('test_user', 'Nikita', 'Prokopchuk', 'password');

INSERT INTO user_groups (name, is_local)
VALUES ('personal', TRUE);

INSERT INTO user_user_groups (id_user, id_user_group, is_admin)
VALUES (1, 1, TRUE);

INSERT INTO task_groups (id_user_group, name)
VALUES (1, 'not assigned');

INSERT INTO places (location) VALUES (0);

INSERT INTO tasks (id_task_group, id_user, id_place, title)
VALUES (1, 1, 1, 'task1'), (1, 1, 1, 'task2'), (1, 1, 1, 'task3');
