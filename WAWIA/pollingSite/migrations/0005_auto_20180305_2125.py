# Generated by Django 2.0.1 on 2018-03-06 05:25

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('pollingSite', '0004_auto_20180301_2338'),
    ]

    operations = [
        migrations.AlterModelOptions(
            name='classroom',
            options={'ordering': ('className',)},
        ),
        migrations.RemoveField(
            model_name='student',
            name='classrooms',
        ),
        migrations.RemoveField(
            model_name='student',
            name='lastname',
        ),
        migrations.AddField(
            model_name='classroom',
            name='students',
            field=models.ManyToManyField(to='pollingSite.Student'),
        ),
        migrations.AddField(
            model_name='poll',
            name='isPollActive',
            field=models.BooleanField(default=False),
        ),
        migrations.AlterField(
            model_name='poll',
            name='startTime',
            field=models.DateTimeField(blank=True, null=True),
        ),
        migrations.AlterField(
            model_name='poll',
            name='stopTime',
            field=models.DateTimeField(blank=True, null=True),
        ),
    ]
