CREATE TABLE `usuario` (
    `id` BIGINT(20) NOT NULL AUTO_INCREMENT,
    `nome` VARCHAR(255) NULL DEFAULT NULL,
    `email` VARCHAR(255) NULL DEFAULT NULL,
    `senha` VARCHAR(255) NULL DEFAULT NULL,
    PRIMARY KEY (`id`)
)
COLLATE='utf8_general_ci'
ENGINE=MyISAM
;

INSERT INTO `usuario` (`id`, `nome`, `email`, `senha`) VALUES (1, 'José Roberto', 'jose@motorista.com.br', '21232f297a57a5a743894a0e4a801fc3');
