#pragma once

const char schemaSqlVersion1[] =

    "CREATE TABLE schema_version ("
    "    id                  INTEGER         DEFAULT 1 PRIMARY KEY ,"
    "    version             INTEGER,"
    "    CHECK               (id = 1)"
    ");"
    ""
    "CREATE TABLE keys ("
    "    id                  INTEGER         PRIMARY KEY AUTOINCREMENT,"
    "    parent_id           INTEGER,"
    "    key                 TEXT            UNIQUE NOT NULL"
    "    );"
    ""
    "CREATE INDEX idx_key_name ON keys (key);"
    ""
    "CREATE TABLE value ("
    "    id                  INTEGER         PRIMARY KEY AUTOINCREMENT,"
    "    key_id              INTEGER         NOT NULL,"
    "    value_name          TEXT            NOT NULL,"
    "    type                TEXT            NOT NULL,"
    "    text_value          TEXT,"
    "    blob_value          BLOB,"
    "    FOREIGN KEY         (key_id)        REFERENCES keys(id),"
    "    CHECK               (length(text_value) > 0 OR length(blob_value) > 0),"
    "    CONSTRAINT uc_id_nameID UNIQUE (key_id, value_name)"
    "    );"
    "CREATE INDEX value_name ON value (value_name);"
    "INSERT INTO schema_version VALUES (1, 100);"
;