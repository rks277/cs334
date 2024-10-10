To ssh:
ssh student334@10.67.67.136 -A
Password: cpsc334!

    https://docs.redhat.com/en/documentation/red_hat_enterprise_linux/9/html/using_systemd_unit_files_to_customize_and_optimize_your_system/assembly_working-with-systemd-unit-files_working-with-systemd#proc_creating-custom-unit-files_assembly_working-with-systemd-unit-files
    
We created a systemd unit file called:
    thanks_koray_for_helping_us_with_this.service

    After=network-online.target

    touch /etc/systemd/system/thanks_koray_for_helping_us_with_this.service
    chmod 666 /etc/systemd/system/thanks_koray_for_helping_us_with_this.service
    chown student334:student334 /etc/systemd/system/thanks_koray_for_helping_us_with_this.service
    systemctl enable thanks_koray_for_helping_us_with_this.service

    systemctl daemon-reload
    sudo systemctl start thanks_koray_for_helping_us_with_this.service
    systemctl status thanks_koray_for_helping_us_with_this.service

We also added the config.txt file as well to the bash script


[Unit]
Description=launch generative art
Requires=graphical.target
After=network.target

[Service]
User=student334
Group=student334
Environment=DISPLAY=:0
WorkingDirectory=/home/student334/Documents/cs334/generative_art/src
ExecStart=/home/student334/Documents/cs334/generative_art/display_on_boot.sh

[Install]
WantedBy=default.target