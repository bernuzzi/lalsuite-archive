--Beginning of script 1--   DatabaseDB2LUOW (SEG6_LHO) [WARNING***Please do not alter this line]--
-- CONNECT TO SEG6_LHO USER XXXX using XXXX;
CREATE TABLESPACE QAASN3 MANAGED BY SYSTEM USING ('QAASN3_TSC');
CREATE TABLE ASN.IBMQREP_APPLYPARMS
(
 QMGR VARCHAR(48) NOT NULL,
 MONITOR_LIMIT INTEGER NOT NULL WITH DEFAULT 10080,
 TRACE_LIMIT INTEGER NOT NULL WITH DEFAULT 10080,
 MONITOR_INTERVAL INTEGER NOT NULL WITH DEFAULT 60000,
 PRUNE_INTERVAL INTEGER NOT NULL WITH DEFAULT 300,
 AUTOSTOP CHARACTER(1) NOT NULL WITH DEFAULT 'N',
 LOGREUSE CHARACTER(1) NOT NULL WITH DEFAULT 'N',
 LOGSTDOUT CHARACTER(1) NOT NULL WITH DEFAULT 'N',
 APPLY_PATH VARCHAR(1040) WITH DEFAULT NULL,
 ARCH_LEVEL CHARACTER(4) NOT NULL WITH DEFAULT '0905',
 TERM CHARACTER(1) NOT NULL WITH DEFAULT 'Y',
 PWDFILE VARCHAR(48) WITH DEFAULT NULL,
 DEADLOCK_RETRIES INTEGER NOT NULL WITH DEFAULT 3,
 SQL_CAP_SCHEMA VARCHAR(128) WITH DEFAULT NULL
)
 IN QAASN3;
ALTER TABLE ASN.IBMQREP_APPLYPARMS
 VOLATILE CARDINALITY;
CREATE UNIQUE INDEX ASN.IX1AQMGRCOL ON ASN.IBMQREP_APPLYPARMS
(
 QMGR ASC
);
CREATE TABLE ASN.IBMQREP_RECVQUEUES
(
 REPQMAPNAME VARCHAR(128) NOT NULL,
 RECVQ VARCHAR(48) NOT NULL,
 SENDQ VARCHAR(48) WITH DEFAULT NULL,
 ADMINQ VARCHAR(48) NOT NULL,
 NUM_APPLY_AGENTS INTEGER NOT NULL WITH DEFAULT 16,
 MEMORY_LIMIT INTEGER NOT NULL WITH DEFAULT 64,
 CAPTURE_SERVER VARCHAR(18) NOT NULL,
 CAPTURE_ALIAS VARCHAR(8) NOT NULL,
 CAPTURE_SCHEMA VARCHAR(128) NOT NULL WITH DEFAULT 'ASN',
 STATE CHARACTER(1) NOT NULL WITH DEFAULT 'A',
 STATE_TIME TIMESTAMP NOT NULL WITH DEFAULT CURRENT TIMESTAMP,
 STATE_INFO CHARACTER(8),
 DESCRIPTION VARCHAR(254),
 SOURCE_TYPE CHARACTER(1) WITH DEFAULT ' ',
 MAXAGENTS_CORRELID INTEGER WITH DEFAULT NULL,
 PRIMARY KEY(RECVQ)
)
 IN QAASN3;
ALTER TABLE ASN.IBMQREP_RECVQUEUES
 VOLATILE CARDINALITY;
CREATE UNIQUE INDEX ASN.IX1REPMAPCOL ON ASN.IBMQREP_RECVQUEUES
(
 REPQMAPNAME ASC
);
CREATE TABLE ASN.IBMQREP_TARGETS
(
 SUBNAME VARCHAR(132) NOT NULL,
 RECVQ VARCHAR(48) NOT NULL,
 SUB_ID INTEGER WITH DEFAULT NULL,
 SOURCE_SERVER VARCHAR(18) NOT NULL,
 SOURCE_ALIAS VARCHAR(8) NOT NULL,
 SOURCE_OWNER VARCHAR(128) NOT NULL,
 SOURCE_NAME VARCHAR(128) NOT NULL,
 SRC_NICKNAME_OWNER VARCHAR(128),
 SRC_NICKNAME VARCHAR(128),
 TARGET_OWNER VARCHAR(128) NOT NULL,
 TARGET_NAME VARCHAR(128) NOT NULL,
 TARGET_TYPE INTEGER NOT NULL WITH DEFAULT 1,
 FEDERATED_TGT_SRVR VARCHAR(18) WITH DEFAULT NULL,
 STATE CHARACTER(1) NOT NULL WITH DEFAULT 'I',
 STATE_TIME TIMESTAMP NOT NULL WITH DEFAULT CURRENT TIMESTAMP,
 STATE_INFO CHARACTER(8),
 SUBTYPE CHARACTER(1) NOT NULL WITH DEFAULT 'U',
 CONFLICT_RULE CHARACTER(1) NOT NULL WITH DEFAULT 'K',
 CONFLICT_ACTION CHARACTER(1) NOT NULL WITH DEFAULT 'I',
 ERROR_ACTION CHARACTER(1) NOT NULL WITH DEFAULT 'Q',
 SPILLQ VARCHAR(48) WITH DEFAULT NULL,
 OKSQLSTATES VARCHAR(128) WITH DEFAULT NULL,
 SUBGROUP VARCHAR(30) WITH DEFAULT NULL,
 SOURCE_NODE SMALLINT NOT NULL WITH DEFAULT 0,
 TARGET_NODE SMALLINT NOT NULL WITH DEFAULT 0,
 GROUP_INIT_ROLE CHARACTER(1) WITH DEFAULT NULL,
 HAS_LOADPHASE CHARACTER(1) NOT NULL WITH DEFAULT 'N',
 LOAD_TYPE SMALLINT NOT NULL WITH DEFAULT 0,
 DESCRIPTION VARCHAR(254),
 SEARCH_CONDITION VARCHAR(2048) WITH DEFAULT NULL,
 MODELQ VARCHAR(36) NOT NULL WITH DEFAULT 'IBMQREP.SPILL.MODELQ',
 CCD_CONDENSED CHARACTER(1) WITH DEFAULT 'Y',
 CCD_COMPLETE CHARACTER(1) WITH DEFAULT 'Y',
 SOURCE_TYPE CHARACTER(1) WITH DEFAULT ' '
)
 IN QAASN3;
ALTER TABLE ASN.IBMQREP_TARGETS
 VOLATILE CARDINALITY;
CREATE UNIQUE INDEX ASN.IX1TARGETS ON ASN.IBMQREP_TARGETS
(
 SUBNAME ASC,
 RECVQ ASC
);
CREATE INDEX ASN.IX2TARGETS ON ASN.IBMQREP_TARGETS
(
 TARGET_OWNER ASC,
 TARGET_NAME ASC,
 RECVQ ASC,
 SOURCE_OWNER ASC,
 SOURCE_NAME ASC
);
CREATE INDEX ASN.IX3TARGETS ON ASN.IBMQREP_TARGETS
(
 RECVQ ASC,
 SUB_ID ASC
);
CREATE TABLE ASN.IBMQREP_TRG_COLS
(
 RECVQ VARCHAR(48) NOT NULL,
 SUBNAME VARCHAR(132) NOT NULL,
 SOURCE_COLNAME VARCHAR(254) NOT NULL,
 TARGET_COLNAME VARCHAR(128) NOT NULL,
 TARGET_COLNO INTEGER WITH DEFAULT NULL,
 MSG_COL_CODEPAGE INTEGER WITH DEFAULT NULL,
 MSG_COL_NUMBER SMALLINT WITH DEFAULT NULL,
 MSG_COL_TYPE SMALLINT WITH DEFAULT NULL,
 MSG_COL_LENGTH INTEGER WITH DEFAULT NULL,
 IS_KEY CHARACTER(1) NOT NULL,
 MAPPING_TYPE CHARACTER(1) WITH DEFAULT NULL,
 SRC_COL_MAP VARCHAR(2000) WITH DEFAULT NULL,
 BEF_TARG_COLNAME VARCHAR(128) WITH DEFAULT NULL
)
 IN QAASN3;
ALTER TABLE ASN.IBMQREP_TRG_COLS
 VOLATILE CARDINALITY;
CREATE UNIQUE INDEX ASN.IX1TRGCOL ON ASN.IBMQREP_TRG_COLS
(
 RECVQ ASC,
 SUBNAME ASC,
 TARGET_COLNAME ASC
);
CREATE TABLE ASN.IBMQREP_SPILLQS
(
 SPILLQ VARCHAR(48) NOT NULL,
 SUBNAME VARCHAR(132) NOT NULL,
 RECVQ VARCHAR(48) NOT NULL,
 PRIMARY KEY(SPILLQ)
)
 IN QAASN3;
ALTER TABLE ASN.IBMQREP_SPILLQS
 VOLATILE CARDINALITY;
CREATE TABLE ASN.IBMQREP_EXCEPTIONS
(
 EXCEPTION_TIME TIMESTAMP NOT NULL WITH DEFAULT CURRENT TIMESTAMP,
 RECVQ VARCHAR(48) NOT NULL,
 SRC_COMMIT_LSN VARCHAR(48) FOR BIT DATA NOT NULL,
 SRC_TRANS_TIME TIMESTAMP NOT NULL,
 SUBNAME VARCHAR(132) NOT NULL,
 REASON CHARACTER(12) NOT NULL,
 SQLCODE INTEGER,
 SQLSTATE CHARACTER(5),
 SQLERRMC VARCHAR(70) FOR BIT DATA,
 OPERATION VARCHAR(18) NOT NULL,
 TEXT CLOB(32768) NOT LOGGED NOT COMPACT NOT NULL,
 IS_APPLIED CHARACTER(1) NOT NULL,
 CONFLICT_RULE CHARACTER(1)
)
 IN QAASN3;
CREATE TABLE ASN.IBMQREP_APPLYTRACE
(
 OPERATION CHARACTER(8) NOT NULL,
 TRACE_TIME TIMESTAMP NOT NULL,
 DESCRIPTION VARCHAR(1024) NOT NULL,
 REASON_CODE INTEGER,
 MQ_CODE INTEGER
)
 IN QAASN3;
ALTER TABLE ASN.IBMQREP_APPLYTRACE
 VOLATILE CARDINALITY;
CREATE INDEX ASN.IX1TRCTMCOL ON ASN.IBMQREP_APPLYTRACE
(
 TRACE_TIME ASC
);
CREATE TABLE ASN.IBMQREP_APPLYMON
(
 MONITOR_TIME TIMESTAMP NOT NULL,
 RECVQ VARCHAR(48) NOT NULL,
 QSTART_TIME TIMESTAMP NOT NULL,
 CURRENT_MEMORY INTEGER NOT NULL,
 QDEPTH INTEGER NOT NULL,
 END2END_LATENCY INTEGER NOT NULL,
 QLATENCY INTEGER NOT NULL,
 APPLY_LATENCY INTEGER NOT NULL,
 TRANS_APPLIED INTEGER NOT NULL,
 ROWS_APPLIED INTEGER NOT NULL,
 TRANS_SERIALIZED INTEGER NOT NULL,
 RI_DEPENDENCIES INTEGER NOT NULL,
 RI_RETRIES INTEGER NOT NULL,
 DEADLOCK_RETRIES INTEGER NOT NULL,
 ROWS_NOT_APPLIED INTEGER NOT NULL,
 MONSTER_TRANS INTEGER NOT NULL,
 MEM_FULL_TIME INTEGER NOT NULL,
 APPLY_SLEEP_TIME INTEGER NOT NULL,
 SPILLED_ROWS INTEGER NOT NULL,
 SPILLEDROWSAPPLIED INTEGER NOT NULL,
 OLDEST_TRANS TIMESTAMP NOT NULL,
 OKSQLSTATE_ERRORS INTEGER NOT NULL,
 HEARTBEAT_LATENCY INTEGER NOT NULL,
 KEY_DEPENDENCIES INTEGER NOT NULL,
 UNIQ_DEPENDENCIES INTEGER NOT NULL,
 UNIQ_RETRIES INTEGER NOT NULL,
 OLDEST_INFLT_TRANS TIMESTAMP,
 JOB_DEPENDENCIES INTEGER,
 CAPTURE_LATENCY INTEGER,
 PRIMARY KEY(MONITOR_TIME, RECVQ)
)
 IN QAASN3;
ALTER TABLE ASN.IBMQREP_APPLYMON
 VOLATILE CARDINALITY;
CREATE TABLE ASN.IBMQREP_DONEMSG
(
 RECVQ VARCHAR(48) NOT NULL,
 MQMSGID CHARACTER(24) FOR BIT DATA NOT NULL,
 PRIMARY KEY(RECVQ, MQMSGID)
)
 IN QAASN3;
ALTER TABLE ASN.IBMQREP_DONEMSG
 VOLATILE CARDINALITY
 APPEND ON;
CREATE TABLE ASN.IBMQREP_SPILLEDROW
(
 SPILLQ VARCHAR(48) NOT NULL,
 MQMSGID CHARACTER(24) FOR BIT DATA NOT NULL,
 PRIMARY KEY(SPILLQ, MQMSGID)
)
 IN QAASN3;
ALTER TABLE ASN.IBMQREP_SPILLEDROW
 VOLATILE CARDINALITY;
CREATE TABLE ASN.IBMQREP_SAVERI
(
 SUBNAME VARCHAR(132) NOT NULL,
 RECVQ VARCHAR(48) NOT NULL,
 CONSTNAME VARCHAR(128) NOT NULL,
 TABSCHEMA VARCHAR(128) NOT NULL,
 TABNAME VARCHAR(128) NOT NULL,
 REFTABSCHEMA VARCHAR(128) NOT NULL,
 REFTABNAME VARCHAR(128) NOT NULL,
 ALTER_RI_DDL VARCHAR(1680) NOT NULL,
 TYPE_OF_LOAD CHARACTER(1) NOT NULL,
 DELETERULE CHARACTER(1),
 UPDATERULE CHARACTER(1)
)
 IN QAASN3;
ALTER TABLE ASN.IBMQREP_SAVERI
 VOLATILE CARDINALITY;
CREATE TABLE ASN.IBMQREP_APPLYENQ
(
 LOCKNAME INTEGER
)
 IN QAASN3;
CREATE TABLE ASN.IBMQREP_APPENVINFO
(
 NAME VARCHAR(30) NOT NULL,
 VALUE VARCHAR(3800)
)
 IN QAASN3;
INSERT INTO ASN.IBMQREP_APPLYPARMS
 (qmgr, monitor_limit, trace_limit, monitor_interval, prune_interval,
 autostop, logreuse, logstdout, arch_level, term, deadlock_retries)
 VALUES
 ('QM1', 10080, 10080, 60000, 300, 'N', 'N', 'N', '0905', 'Y', 3);
-- COMMIT;